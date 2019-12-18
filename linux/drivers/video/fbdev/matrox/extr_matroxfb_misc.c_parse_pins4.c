#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int ref_freq; } ;
struct TYPE_16__ {TYPE_7__ pll; } ;
struct TYPE_13__ {int system; } ;
struct TYPE_12__ {int memrdbk; int opt; void* opt3; void* mctlwtst; } ;
struct TYPE_14__ {TYPE_5__ pll; TYPE_4__ reg; } ;
struct TYPE_10__ {int vcomax; } ;
struct TYPE_9__ {int vcomax; } ;
struct TYPE_11__ {TYPE_2__ pixel; TYPE_1__ system; } ;
struct matrox_fb_info {TYPE_8__ features; TYPE_6__ values; TYPE_3__ limits; } ;
struct matrox_bios {int* pins; } ;

/* Variables and functions */
 void* get_unaligned_le32 (int*) ; 

__attribute__((used)) static int parse_pins4(struct matrox_fb_info *minfo,
		       const struct matrox_bios *bd)
{
	minfo->limits.pixel.vcomax	= (bd->pins[ 39] == 0xFF) ? 230000			: bd->pins[ 39] * 4000;
	minfo->limits.system.vcomax	= (bd->pins[ 38] == 0xFF) ? minfo->limits.pixel.vcomax	: bd->pins[ 38] * 4000;
	minfo->values.reg.mctlwtst	= get_unaligned_le32(bd->pins + 71);
	minfo->values.reg.memrdbk	= ((bd->pins[87] << 21) & 0x1E000000) |
					  ((bd->pins[87] << 22) & 0x00C00000) |
					  ((bd->pins[86] <<  1) & 0x000001E0) |
					  ( bd->pins[86]        & 0x0000000F);
	minfo->values.reg.opt		= ((bd->pins[53] << 15) & 0x00400000) |
					  ((bd->pins[53] << 22) & 0x10000000) |
					  ((bd->pins[53] <<  7) & 0x00001C00);
	minfo->values.reg.opt3		= get_unaligned_le32(bd->pins + 67);
	minfo->values.pll.system	= (bd->pins[ 65] == 0xFF) ? 200000 			: bd->pins[ 65] * 4000;
	minfo->features.pll.ref_freq	= (bd->pins[ 92] & 0x01) ? 14318 : 27000;
	return 0;
}