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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  vgabase; } ;
struct s3fb_info {int chip; TYPE_1__ state; } ;

/* Variables and functions */
 int CHIP_360_TRIO3D_1X ; 
 int CHIP_362_TRIO3D_2X ; 
 int CHIP_368_TRIO3D_2X ; 
 int CHIP_36X_TRIO3D_1X_2X ; 
 int CHIP_375_VIRGE_DX ; 
 int CHIP_385_VIRGE_GX ; 
 int CHIP_732_TRIO32 ; 
 int CHIP_764_TRIO64 ; 
 int CHIP_765_TRIO64VP ; 
 int CHIP_775_TRIO64V2_DX ; 
 int CHIP_785_TRIO64V2_GX ; 
 int CHIP_UNKNOWN ; 
 int CHIP_XXX_TRIO ; 
 int CHIP_XXX_TRIO64V2_DXGX ; 
 int CHIP_XXX_VIRGE_DXGX ; 
 int vga_rcrt (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int s3_identification(struct s3fb_info *par)
{
	int chip = par->chip;

	if (chip == CHIP_XXX_TRIO) {
		u8 cr30 = vga_rcrt(par->state.vgabase, 0x30);
		u8 cr2e = vga_rcrt(par->state.vgabase, 0x2e);
		u8 cr2f = vga_rcrt(par->state.vgabase, 0x2f);

		if ((cr30 == 0xE0) || (cr30 == 0xE1)) {
			if (cr2e == 0x10)
				return CHIP_732_TRIO32;
			if (cr2e == 0x11) {
				if (! (cr2f & 0x40))
					return CHIP_764_TRIO64;
				else
					return CHIP_765_TRIO64VP;
			}
		}
	}

	if (chip == CHIP_XXX_TRIO64V2_DXGX) {
		u8 cr6f = vga_rcrt(par->state.vgabase, 0x6f);

		if (! (cr6f & 0x01))
			return CHIP_775_TRIO64V2_DX;
		else
			return CHIP_785_TRIO64V2_GX;
	}

	if (chip == CHIP_XXX_VIRGE_DXGX) {
		u8 cr6f = vga_rcrt(par->state.vgabase, 0x6f);

		if (! (cr6f & 0x01))
			return CHIP_375_VIRGE_DX;
		else
			return CHIP_385_VIRGE_GX;
	}

	if (chip == CHIP_36X_TRIO3D_1X_2X) {
		switch (vga_rcrt(par->state.vgabase, 0x2f)) {
		case 0x00:
			return CHIP_360_TRIO3D_1X;
		case 0x01:
			return CHIP_362_TRIO3D_2X;
		case 0x02:
			return CHIP_368_TRIO3D_2X;
		}
	}

	return CHIP_UNKNOWN;
}