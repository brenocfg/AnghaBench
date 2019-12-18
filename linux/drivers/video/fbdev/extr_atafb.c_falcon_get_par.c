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
struct falcon_hw {int st_shift; int f_shift; int sync; int xoffset; int ste_mode; int mono; int /*<<< orphan*/  vss; int /*<<< orphan*/  vde; int /*<<< orphan*/  vdb; int /*<<< orphan*/  vbe; int /*<<< orphan*/  vbb; int /*<<< orphan*/  vft; int /*<<< orphan*/  hss; int /*<<< orphan*/  hde; int /*<<< orphan*/  hdb; int /*<<< orphan*/  hbe; int /*<<< orphan*/  hbb; int /*<<< orphan*/  hht; int /*<<< orphan*/  vid_mode; int /*<<< orphan*/  vid_control; int /*<<< orphan*/  line_offset; int /*<<< orphan*/  line_width; } ;
struct TYPE_5__ {struct falcon_hw falcon; } ;
struct atafb_par {int /*<<< orphan*/  screen_base; TYPE_1__ hw; } ;
struct TYPE_8__ {int /*<<< orphan*/  off_next; int /*<<< orphan*/  scn_width; } ;
struct TYPE_7__ {int syncmode; int bas_hi; int bas_md; int bas_lo; } ;
struct TYPE_6__ {int st_shift; int f_shift; int xoffset; int /*<<< orphan*/  vss; int /*<<< orphan*/  vde; int /*<<< orphan*/  vdb; int /*<<< orphan*/  vbe; int /*<<< orphan*/  vbb; int /*<<< orphan*/  vft; int /*<<< orphan*/  hss; int /*<<< orphan*/  hde; int /*<<< orphan*/  hdb; int /*<<< orphan*/  hbe; int /*<<< orphan*/  hbb; int /*<<< orphan*/  hht; int /*<<< orphan*/  mode; int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  atari_stram_to_virt (unsigned long) ; 
 TYPE_4__ shifter_f030 ; 
 TYPE_3__ shifter_st ; 
 TYPE_2__ videl ; 

__attribute__((used)) static void falcon_get_par(struct atafb_par *par)
{
	unsigned long addr;
	struct falcon_hw *hw = &par->hw.falcon;

	hw->line_width = shifter_f030.scn_width;
	hw->line_offset = shifter_f030.off_next;
	hw->st_shift = videl.st_shift & 0x300;
	hw->f_shift = videl.f_shift;
	hw->vid_control = videl.control;
	hw->vid_mode = videl.mode;
	hw->sync = shifter_st.syncmode & 0x1;
	hw->xoffset = videl.xoffset & 0xf;
	hw->hht = videl.hht;
	hw->hbb = videl.hbb;
	hw->hbe = videl.hbe;
	hw->hdb = videl.hdb;
	hw->hde = videl.hde;
	hw->hss = videl.hss;
	hw->vft = videl.vft;
	hw->vbb = videl.vbb;
	hw->vbe = videl.vbe;
	hw->vdb = videl.vdb;
	hw->vde = videl.vde;
	hw->vss = videl.vss;

	addr = (shifter_st.bas_hi & 0xff) << 16 |
	       (shifter_st.bas_md & 0xff) << 8  |
	       (shifter_st.bas_lo & 0xff);
	par->screen_base = atari_stram_to_virt(addr);

	/* derived parameters */
	hw->ste_mode = (hw->f_shift & 0x510) == 0 && hw->st_shift == 0x100;
	hw->mono = (hw->f_shift & 0x400) ||
	           ((hw->f_shift & 0x510) == 0 && hw->st_shift == 0x200);
}