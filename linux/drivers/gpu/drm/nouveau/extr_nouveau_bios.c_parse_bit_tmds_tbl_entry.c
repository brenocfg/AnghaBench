#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_2__ {void* output1_script_ptr; void* output0_script_ptr; } ;
struct nvbios {int* data; TYPE_1__ tmds; } ;
struct nouveau_drm {int dummy; } ;
struct drm_device {int dummy; } ;
struct bit_entry {int length; size_t offset; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*,...) ; 
 int /*<<< orphan*/  NV_WARN (struct nouveau_drm*,char*) ; 
 void* ROM16 (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 

__attribute__((used)) static int parse_bit_tmds_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{
	/*
	 * Parses the pointer to the TMDS table
	 *
	 * Starting at bitentry->offset:
	 *
	 * offset + 0  (16 bits): TMDS table pointer
	 *
	 * The TMDS table is typically found just before the DCB table, with a
	 * characteristic signature of 0x11,0x13 (1.1 being version, 0x13 being
	 * length?)
	 *
	 * At offset +7 is a pointer to a script, which I don't know how to
	 * run yet.
	 * At offset +9 is a pointer to another script, likewise
	 * Offset +11 has a pointer to a table where the first word is a pxclk
	 * frequency and the second word a pointer to a script, which should be
	 * run if the comparison pxclk frequency is less than the pxclk desired.
	 * This repeats for decreasing comparison frequencies
	 * Offset +13 has a pointer to a similar table
	 * The selection of table (and possibly +7/+9 script) is dictated by
	 * "or" from the DCB.
	 */

	struct nouveau_drm *drm = nouveau_drm(dev);
	uint16_t tmdstableptr, script1, script2;

	if (bitentry->length != 2) {
		NV_ERROR(drm, "Do not understand BIT TMDS table\n");
		return -EINVAL;
	}

	tmdstableptr = ROM16(bios->data[bitentry->offset]);
	if (!tmdstableptr) {
		NV_INFO(drm, "Pointer to TMDS table not found\n");
		return -EINVAL;
	}

	NV_INFO(drm, "TMDS table version %d.%d\n",
		bios->data[tmdstableptr] >> 4, bios->data[tmdstableptr] & 0xf);

	/* nv50+ has v2.0, but we don't parse it atm */
	if (bios->data[tmdstableptr] != 0x11)
		return -ENOSYS;

	/*
	 * These two scripts are odd: they don't seem to get run even when
	 * they are not stubbed.
	 */
	script1 = ROM16(bios->data[tmdstableptr + 7]);
	script2 = ROM16(bios->data[tmdstableptr + 9]);
	if (bios->data[script1] != 'q' || bios->data[script2] != 'q')
		NV_WARN(drm, "TMDS table script pointers not stubbed\n");

	bios->tmds.output0_script_ptr = ROM16(bios->data[tmdstableptr + 11]);
	bios->tmds.output1_script_ptr = ROM16(bios->data[tmdstableptr + 13]);

	return 0;
}