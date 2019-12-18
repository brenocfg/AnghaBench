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
struct vt8623fb_info {TYPE_1__ state; } ;
struct fb_info {int /*<<< orphan*/  node; struct vt8623fb_info* par; } ;

/* Variables and functions */
 int VGA_MIS_ENB_PLL_LOAD ; 
 int /*<<< orphan*/  VGA_MIS_R ; 
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  fb_err (struct fb_info*,char*) ; 
 int svga_compute_pll (int /*<<< orphan*/ *,int,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svga_wseq_mask (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int vga_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vt8623_pll ; 

__attribute__((used)) static void vt8623_set_pixclock(struct fb_info *info, u32 pixclock)
{
	struct vt8623fb_info *par = info->par;
	u16 m, n, r;
	u8 regval;
	int rv;

	rv = svga_compute_pll(&vt8623_pll, 1000000000 / pixclock, &m, &n, &r, info->node);
	if (rv < 0) {
		fb_err(info, "cannot set requested pixclock, keeping old value\n");
		return;
	}

	/* Set VGA misc register  */
	regval = vga_r(par->state.vgabase, VGA_MIS_R);
	vga_w(par->state.vgabase, VGA_MIS_W, regval | VGA_MIS_ENB_PLL_LOAD);

	/* Set clock registers */
	vga_wseq(par->state.vgabase, 0x46, (n  | (r << 6)));
	vga_wseq(par->state.vgabase, 0x47, m);

	udelay(1000);

	/* PLL reset */
	svga_wseq_mask(par->state.vgabase, 0x40, 0x02, 0x02);
	svga_wseq_mask(par->state.vgabase, 0x40, 0x00, 0x02);
}