#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_20__ {int mctlwtst; int maccess; int mctlwtst_core; void* memrdbk; void* memmisc; void* opt3; void* opt2; void* opt; } ;
struct TYPE_19__ {int ddr; int dll; int emrswen; } ;
struct TYPE_16__ {int system; int video; } ;
struct TYPE_11__ {TYPE_9__ reg; TYPE_8__ memory; TYPE_5__ pll; } ;
struct TYPE_17__ {int ref_freq; } ;
struct TYPE_18__ {TYPE_6__ pll; } ;
struct TYPE_14__ {unsigned int vcomax; unsigned int vcomin; } ;
struct TYPE_13__ {unsigned int vcomax; unsigned int vcomin; } ;
struct TYPE_12__ {int vcomax; int vcomin; } ;
struct TYPE_15__ {TYPE_3__ system; TYPE_2__ video; TYPE_1__ pixel; } ;
struct matrox_fb_info {int max_pixel_clock_panellink; TYPE_10__ values; TYPE_7__ features; TYPE_4__ limits; } ;
struct matrox_bios {int* pins; } ;

/* Variables and functions */
 void* get_unaligned_le32 (int*) ; 

__attribute__((used)) static int parse_pins5(struct matrox_fb_info *minfo,
		       const struct matrox_bios *bd)
{
	unsigned int mult;
	
	mult = bd->pins[4]?8000:6000;
	
	minfo->limits.pixel.vcomax	= (bd->pins[ 38] == 0xFF) ? 600000			: bd->pins[ 38] * mult;
	minfo->limits.system.vcomax	= (bd->pins[ 36] == 0xFF) ? minfo->limits.pixel.vcomax	: bd->pins[ 36] * mult;
	minfo->limits.video.vcomax	= (bd->pins[ 37] == 0xFF) ? minfo->limits.system.vcomax	: bd->pins[ 37] * mult;
	minfo->limits.pixel.vcomin	= (bd->pins[123] == 0xFF) ? 256000			: bd->pins[123] * mult;
	minfo->limits.system.vcomin	= (bd->pins[121] == 0xFF) ? minfo->limits.pixel.vcomin	: bd->pins[121] * mult;
	minfo->limits.video.vcomin	= (bd->pins[122] == 0xFF) ? minfo->limits.system.vcomin	: bd->pins[122] * mult;
	minfo->values.pll.system	=
	minfo->values.pll.video		= (bd->pins[ 92] == 0xFF) ? 284000			: bd->pins[ 92] * 4000;
	minfo->values.reg.opt		= get_unaligned_le32(bd->pins + 48);
	minfo->values.reg.opt2		= get_unaligned_le32(bd->pins + 52);
	minfo->values.reg.opt3		= get_unaligned_le32(bd->pins + 94);
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 98);
	minfo->values.reg.memmisc	= get_unaligned_le32(bd->pins + 102);
	minfo->values.reg.memrdbk	= get_unaligned_le32(bd->pins + 106);
	minfo->features.pll.ref_freq	= (bd->pins[110] & 0x01) ? 14318 : 27000;
	minfo->values.memory.ddr	= (bd->pins[114] & 0x60) == 0x20;
	minfo->values.memory.dll	= (bd->pins[115] & 0x02) != 0;
	minfo->values.memory.emrswen	= (bd->pins[115] & 0x01) != 0;
	minfo->values.reg.maccess	= minfo->values.memory.emrswen ? 0x00004000 : 0x00000000;
	if (bd->pins[115] & 4) {
		minfo->values.reg.mctlwtst_core = minfo->values.reg.mctlwtst;
	} else {
		u_int32_t wtst_xlat[] = { 0, 1, 5, 6, 7, 5, 2, 3 };
		minfo->values.reg.mctlwtst_core = (minfo->values.reg.mctlwtst & ~7) |
						  wtst_xlat[minfo->values.reg.mctlwtst & 7];
	}
	minfo->max_pixel_clock_panellink = bd->pins[47] * 4000;
	return 0;
}