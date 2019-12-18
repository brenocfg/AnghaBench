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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  vgabase; } ;
struct s3fb_info {scalar_t__ chip; TYPE_1__ state; } ;
struct fb_info {int /*<<< orphan*/  node; struct s3fb_info* par; } ;

/* Variables and functions */
 scalar_t__ CHIP_260_VIRGE_MX ; 
 scalar_t__ CHIP_357_VIRGE_GX2 ; 
 scalar_t__ CHIP_359_VIRGE_GX2P ; 
 scalar_t__ CHIP_360_TRIO3D_1X ; 
 scalar_t__ CHIP_362_TRIO3D_2X ; 
 scalar_t__ CHIP_365_TRIO3D ; 
 scalar_t__ CHIP_368_TRIO3D_2X ; 
 int VGA_MIS_ENB_PLL_LOAD ; 
 int /*<<< orphan*/  VGA_MIS_R ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*) ; 
 int /*<<< orphan*/  s3_pll ; 
 int /*<<< orphan*/  s3_trio3d_pll ; 
 int svga_compute_pll (int /*<<< orphan*/ *,int,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int vga_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vga_rseq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void s3_set_pixclock(struct fb_info *info, u32 pixclock)
{
	struct s3fb_info *par = info->par;
	u16 m, n, r;
	u8 regval;
	int rv;

	rv = svga_compute_pll((par->chip == CHIP_365_TRIO3D) ? &s3_trio3d_pll : &s3_pll,
			      1000000000 / pixclock, &m, &n, &r, info->node);
	if (rv < 0) {
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		return;
	}

	/* Set VGA misc register  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);

	/* Set S3 clock registers */
	if (par->chip == CHIP_357_VIRGE_GX2 ||
	    par->chip == CHIP_359_VIRGE_GX2P ||
	    par->chip == CHIP_360_TRIO3D_1X ||
	    par->chip == CHIP_362_TRIO3D_2X ||
	    par->chip == CHIP_368_TRIO3D_2X ||
	    par->chip == CHIP_260_VIRGE_MX) {
		vga_wseq(par->state.vgabase, 0x12, (n - 2) | ((r & 3) << 6));	/* n and two bits of r */
		vga_wseq(par->state.vgabase, 0x29, r >> 2); /* remaining highest bit of r */
	} else
		vga_wseq(par->state.vgabase, 0x12, (n - 2) | (r << 5));
	vga_wseq(par->state.vgabase, 0x13, m - 2);

	udelay(1000);

	/* Activate clock - write 0, 1, 0 to seq/15 bit 5 */
	regval = vga_rseq (par->state.vgabase, 0x15); /* | 0x80; */
	vga_wseq(par->state.vgabase, 0x15, regval & ~(1<<5));
	vga_wseq(par->state.vgabase, 0x15, regval |  (1<<5));
	vga_wseq(par->state.vgabase, 0x15, regval & ~(1<<5));
}