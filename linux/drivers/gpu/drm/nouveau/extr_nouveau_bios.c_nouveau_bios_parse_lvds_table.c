#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_4__ {int duallink_transition_clk; size_t xlated_entry; size_t lvdsmanufacturerpointer; int power_off_for_reset; int reset_after_pclk_change; int dual_link; int link_c_increment; int if_is_24bit; int strapless_is_24bit; int /*<<< orphan*/  fpxlatemanufacturertableptr; } ;
struct TYPE_3__ {int lvds_single_a_script_ptr; } ;
struct nvbios {int chip_version; int* data; TYPE_2__ fp; TYPE_1__ legacy; } ;
struct nouveau_drm {struct nvbios vbios; } ;
struct lvdstableheader {int lvds_ver; size_t headerlen; int recordlen; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int ROM16 (int) ; 
 int get_fp_strap (struct drm_device*,struct nvbios*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int parse_lvds_manufacturer_table_header (struct drm_device*,struct nvbios*,struct lvdstableheader*) ; 

int nouveau_bios_parse_lvds_table(struct drm_device *dev, int pxclk, bool *dl, bool *if_is_24bit)
{
	/*
	 * The LVDS table header is (mostly) described in
	 * parse_lvds_manufacturer_table_header(): the BIT header additionally
	 * contains the dual-link transition pxclk (in 10s kHz), at byte 5 - if
	 * straps are not being used for the panel, this specifies the frequency
	 * at which modes should be set up in the dual link style.
	 *
	 * Following the header, the BMP (ver 0xa) table has several records,
	 * indexed by a separate xlat table, indexed in turn by the fp strap in
	 * EXTDEV_BOOT. Each record had a config byte, followed by 6 script
	 * numbers for use by INIT_SUB which controlled panel init and power,
	 * and finally a dword of ms to sleep between power off and on
	 * operations.
	 *
	 * In the BIT versions, the table following the header serves as an
	 * integrated config and xlat table: the records in the table are
	 * indexed by the FP strap nibble in EXTDEV_BOOT, and each record has
	 * two bytes - the first as a config byte, the second for indexing the
	 * fp mode table pointed to by the BIT 'D' table
	 *
	 * DDC is not used until after card init, so selecting the correct table
	 * entry and setting the dual link flag for EDID equipped panels,
	 * requiring tests against the native-mode pixel clock, cannot be done
	 * until later, when this function should be called with non-zero pxclk
	 */
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	int fpstrapping = get_fp_strap(dev, bios), lvdsmanufacturerindex = 0;
	struct lvdstableheader lth;
	uint16_t lvdsofs;
	int ret, chip_version = bios->chip_version;

	ret = parse_lvds_manufacturer_table_header(dev, bios, &lth);
	if (ret)
		return ret;

	switch (lth.lvds_ver) {
	case 0x0a:	/* pre NV40 */
		lvdsmanufacturerindex = bios->data[
					bios->fp.fpxlatemanufacturertableptr +
					fpstrapping];

		/* we're done if this isn't the EDID panel case */
		if (!pxclk)
			break;

		if (chip_version < 0x25) {
			/* nv17 behaviour
			 *
			 * It seems the old style lvds script pointer is reused
			 * to select 18/24 bit colour depth for EDID panels.
			 */
			lvdsmanufacturerindex =
				(bios->legacy.lvds_single_a_script_ptr & 1) ?
									2 : 0;
			if (pxclk >= bios->fp.duallink_transition_clk)
				lvdsmanufacturerindex++;
		} else if (chip_version < 0x30) {
			/* nv28 behaviour (off-chip encoder)
			 *
			 * nv28 does a complex dance of first using byte 121 of
			 * the EDID to choose the lvdsmanufacturerindex, then
			 * later attempting to match the EDID manufacturer and
			 * product IDs in a table (signature 'pidt' (panel id
			 * table?)), setting an lvdsmanufacturerindex of 0 and
			 * an fp strap of the match index (or 0xf if none)
			 */
			lvdsmanufacturerindex = 0;
		} else {
			/* nv31, nv34 behaviour */
			lvdsmanufacturerindex = 0;
			if (pxclk >= bios->fp.duallink_transition_clk)
				lvdsmanufacturerindex = 2;
			if (pxclk >= 140000)
				lvdsmanufacturerindex = 3;
		}

		/*
		 * nvidia set the high nibble of (cr57=f, cr58) to
		 * lvdsmanufacturerindex in this case; we don't
		 */
		break;
	case 0x30:	/* NV4x */
	case 0x40:	/* G80/G90 */
		lvdsmanufacturerindex = fpstrapping;
		break;
	default:
		NV_ERROR(drm, "LVDS table revision not currently supported\n");
		return -ENOSYS;
	}

	lvdsofs = bios->fp.xlated_entry = bios->fp.lvdsmanufacturerpointer + lth.headerlen + lth.recordlen * lvdsmanufacturerindex;
	switch (lth.lvds_ver) {
	case 0x0a:
		bios->fp.power_off_for_reset = bios->data[lvdsofs] & 1;
		bios->fp.reset_after_pclk_change = bios->data[lvdsofs] & 2;
		bios->fp.dual_link = bios->data[lvdsofs] & 4;
		bios->fp.link_c_increment = bios->data[lvdsofs] & 8;
		*if_is_24bit = bios->data[lvdsofs] & 16;
		break;
	case 0x30:
	case 0x40:
		/*
		 * No sign of the "power off for reset" or "reset for panel
		 * on" bits, but it's safer to assume we should
		 */
		bios->fp.power_off_for_reset = true;
		bios->fp.reset_after_pclk_change = true;

		/*
		 * It's ok lvdsofs is wrong for nv4x edid case; dual_link is
		 * over-written, and if_is_24bit isn't used
		 */
		bios->fp.dual_link = bios->data[lvdsofs] & 1;
		bios->fp.if_is_24bit = bios->data[lvdsofs] & 2;
		bios->fp.strapless_is_24bit = bios->data[bios->fp.lvdsmanufacturerpointer + 4];
		bios->fp.duallink_transition_clk = ROM16(bios->data[bios->fp.lvdsmanufacturerpointer + 5]) * 10;
		break;
	}

	/* set dual_link flag for EDID case */
	if (pxclk && (chip_version < 0x25 || chip_version > 0x28))
		bios->fp.dual_link = (pxclk >= bios->fp.duallink_transition_clk);

	*dl = bios->fp.dual_link;

	return 0;
}