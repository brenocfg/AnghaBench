#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_8__ {int duallink_transition_clk; int fptablepointer; int fpxlatetableptr; int xlatwidth; int lvdsmanufacturerpointer; int fpxlatemanufacturertableptr; } ;
struct TYPE_5__ {int crt; int tv; int panel; } ;
struct TYPE_7__ {int mem_init_tbl_ptr; int sdr_seq_tbl_ptr; int ddr_seq_tbl_ptr; int lvds_single_a_script_ptr; TYPE_1__ i2c_indices; } ;
struct TYPE_6__ {int output0_script_ptr; int output1_script_ptr; } ;
struct nvbios {int* data; int digital_min_front_porch; int fmaxvco; int fminvco; int feature_byte; int old_style_init; int init_script_tbls_ptr; int extra_init_script_tbl_ptr; int pll_limit_tbl_ptr; TYPE_4__ fp; TYPE_3__ legacy; TYPE_2__ tmds; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,int,int) ; 
 int ROM16 (int) ; 
 void* ROM32 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_cksum (int*,int) ; 
 int /*<<< orphan*/  parse_script_table_pointers (struct nvbios*,unsigned int) ; 

__attribute__((used)) static int parse_bmp_structure(struct drm_device *dev, struct nvbios *bios, unsigned int offset)
{
	/*
	 * Parses the BMP structure for useful things, but does not act on them
	 *
	 * offset +   5: BMP major version
	 * offset +   6: BMP minor version
	 * offset +   9: BMP feature byte
	 * offset +  10: BCD encoded BIOS version
	 *
	 * offset +  18: init script table pointer (for bios versions < 5.10h)
	 * offset +  20: extra init script table pointer (for bios
	 * versions < 5.10h)
	 *
	 * offset +  24: memory init table pointer (used on early bios versions)
	 * offset +  26: SDR memory sequencing setup data table
	 * offset +  28: DDR memory sequencing setup data table
	 *
	 * offset +  54: index of I2C CRTC pair to use for CRT output
	 * offset +  55: index of I2C CRTC pair to use for TV output
	 * offset +  56: index of I2C CRTC pair to use for flat panel output
	 * offset +  58: write CRTC index for I2C pair 0
	 * offset +  59: read CRTC index for I2C pair 0
	 * offset +  60: write CRTC index for I2C pair 1
	 * offset +  61: read CRTC index for I2C pair 1
	 *
	 * offset +  67: maximum internal PLL frequency (single stage PLL)
	 * offset +  71: minimum internal PLL frequency (single stage PLL)
	 *
	 * offset +  75: script table pointers, as described in
	 * parse_script_table_pointers
	 *
	 * offset +  89: TMDS single link output A table pointer
	 * offset +  91: TMDS single link output B table pointer
	 * offset +  95: LVDS single link output A table pointer
	 * offset + 105: flat panel timings table pointer
	 * offset + 107: flat panel strapping translation table pointer
	 * offset + 117: LVDS manufacturer panel config table pointer
	 * offset + 119: LVDS manufacturer strapping translation table pointer
	 *
	 * offset + 142: PLL limits table pointer
	 *
	 * offset + 156: minimum pixel clock for LVDS dual link
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t *bmp = &bios->data[offset], bmp_version_major, bmp_version_minor;
	uint16_t bmplength;
	uint16_t legacy_scripts_offset, legacy_i2c_offset;

	/* load needed defaults in case we can't parse this info */
	bios->digital_min_front_porch = 0x4b;
	bios->fmaxvco = 256000;
	bios->fminvco = 128000;
	bios->fp.duallink_transition_clk = 90000;

	bmp_version_major = bmp[5];
	bmp_version_minor = bmp[6];

	NV_INFO(drm, "BMP version %d.%d\n",
		 bmp_version_major, bmp_version_minor);

	/*
	 * Make sure that 0x36 is blank and can't be mistaken for a DCB
	 * pointer on early versions
	 */
	if (bmp_version_major < 5)
		*(uint16_t *)&bios->data[0x36] = 0;

	/*
	 * Seems that the minor version was 1 for all major versions prior
	 * to 5. Version 6 could theoretically exist, but I suspect BIT
	 * happened instead.
	 */
	if ((bmp_version_major < 5 && bmp_version_minor != 1) || bmp_version_major > 5) {
		NV_ERROR(drm, "You have an unsupported BMP version. "
				"Please send in your bios\n");
		return -ENOSYS;
	}

	if (bmp_version_major == 0)
		/* nothing that's currently useful in this version */
		return 0;
	else if (bmp_version_major == 1)
		bmplength = 44; /* exact for 1.01 */
	else if (bmp_version_major == 2)
		bmplength = 48; /* exact for 2.01 */
	else if (bmp_version_major == 3)
		bmplength = 54;
		/* guessed - mem init tables added in this version */
	else if (bmp_version_major == 4 || bmp_version_minor < 0x1)
		/* don't know if 5.0 exists... */
		bmplength = 62;
		/* guessed - BMP I2C indices added in version 4*/
	else if (bmp_version_minor < 0x6)
		bmplength = 67; /* exact for 5.01 */
	else if (bmp_version_minor < 0x10)
		bmplength = 75; /* exact for 5.06 */
	else if (bmp_version_minor == 0x10)
		bmplength = 89; /* exact for 5.10h */
	else if (bmp_version_minor < 0x14)
		bmplength = 118; /* exact for 5.11h */
	else if (bmp_version_minor < 0x24)
		/*
		 * Not sure of version where pll limits came in;
		 * certainly exist by 0x24 though.
		 */
		/* length not exact: this is long enough to get lvds members */
		bmplength = 123;
	else if (bmp_version_minor < 0x27)
		/*
		 * Length not exact: this is long enough to get pll limit
		 * member
		 */
		bmplength = 144;
	else
		/*
		 * Length not exact: this is long enough to get dual link
		 * transition clock.
		 */
		bmplength = 158;

	/* checksum */
	if (nv_cksum(bmp, 8)) {
		NV_ERROR(drm, "Bad BMP checksum\n");
		return -EINVAL;
	}

	/*
	 * Bit 4 seems to indicate either a mobile bios or a quadro card --
	 * mobile behaviour consistent (nv11+), quadro only seen nv18gl-nv36gl
	 * (not nv10gl), bit 5 that the flat panel tables are present, and
	 * bit 6 a tv bios.
	 */
	bios->feature_byte = bmp[9];

	if (bmp_version_major < 5 || bmp_version_minor < 0x10)
		bios->old_style_init = true;
	legacy_scripts_offset = 18;
	if (bmp_version_major < 2)
		legacy_scripts_offset -= 4;
	bios->init_script_tbls_ptr = ROM16(bmp[legacy_scripts_offset]);
	bios->extra_init_script_tbl_ptr = ROM16(bmp[legacy_scripts_offset + 2]);

	if (bmp_version_major > 2) {	/* appears in BMP 3 */
		bios->legacy.mem_init_tbl_ptr = ROM16(bmp[24]);
		bios->legacy.sdr_seq_tbl_ptr = ROM16(bmp[26]);
		bios->legacy.ddr_seq_tbl_ptr = ROM16(bmp[28]);
	}

	legacy_i2c_offset = 0x48;	/* BMP version 2 & 3 */
	if (bmplength > 61)
		legacy_i2c_offset = offset + 54;
	bios->legacy.i2c_indices.crt = bios->data[legacy_i2c_offset];
	bios->legacy.i2c_indices.tv = bios->data[legacy_i2c_offset + 1];
	bios->legacy.i2c_indices.panel = bios->data[legacy_i2c_offset + 2];

	if (bmplength > 74) {
		bios->fmaxvco = ROM32(bmp[67]);
		bios->fminvco = ROM32(bmp[71]);
	}
	if (bmplength > 88)
		parse_script_table_pointers(bios, offset + 75);
	if (bmplength > 94) {
		bios->tmds.output0_script_ptr = ROM16(bmp[89]);
		bios->tmds.output1_script_ptr = ROM16(bmp[91]);
		/*
		 * Never observed in use with lvds scripts, but is reused for
		 * 18/24 bit panel interface default for EDID equipped panels
		 * (if_is_24bit not set directly to avoid any oscillation).
		 */
		bios->legacy.lvds_single_a_script_ptr = ROM16(bmp[95]);
	}
	if (bmplength > 108) {
		bios->fp.fptablepointer = ROM16(bmp[105]);
		bios->fp.fpxlatetableptr = ROM16(bmp[107]);
		bios->fp.xlatwidth = 1;
	}
	if (bmplength > 120) {
		bios->fp.lvdsmanufacturerpointer = ROM16(bmp[117]);
		bios->fp.fpxlatemanufacturertableptr = ROM16(bmp[119]);
	}
#if 0
	if (bmplength > 143)
		bios->pll_limit_tbl_ptr = ROM16(bmp[142]);
#endif

	if (bmplength > 157)
		bios->fp.duallink_transition_clk = ROM16(bmp[156]) * 10;

	return 0;
}