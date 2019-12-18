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
struct vgastate {int /*<<< orphan*/  vgabase; } ;
struct TYPE_2__ {int HorizontalTotal; int HorizDisplayEnd; int StartHorizRetrace; int EndHorizRetrace; int Overflow; int StartVertRetrace; int EndVertRetrace; int ModeControl; int CrtCtrlIndex; int /*<<< orphan*/  SeqCtrlIndex; int /*<<< orphan*/  ClockingMode; int /*<<< orphan*/  CrtMiscIO; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGA_MIS_W ; 
 int /*<<< orphan*/  VGA_SEQ_CLOCK_MODE ; 
 int /*<<< orphan*/  VGA_SEQ_I ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_lock ; 
 TYPE_1__ vga_state ; 
 int /*<<< orphan*/  vga_video_port_reg ; 
 int /*<<< orphan*/  vga_video_port_val ; 
 int /*<<< orphan*/  vga_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wseq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vga_vesa_unblank(struct vgastate *state)
{
	/* restore original values of VGA controller registers */
	raw_spin_lock_irq(&vga_lock);
	vga_w(state->vgabase, VGA_MIS_W, vga_state.CrtMiscIO);

	outb_p(0x00, vga_video_port_reg);	/* HorizontalTotal */
	outb_p(vga_state.HorizontalTotal, vga_video_port_val);
	outb_p(0x01, vga_video_port_reg);	/* HorizDisplayEnd */
	outb_p(vga_state.HorizDisplayEnd, vga_video_port_val);
	outb_p(0x04, vga_video_port_reg);	/* StartHorizRetrace */
	outb_p(vga_state.StartHorizRetrace, vga_video_port_val);
	outb_p(0x05, vga_video_port_reg);	/* EndHorizRetrace */
	outb_p(vga_state.EndHorizRetrace, vga_video_port_val);
	outb_p(0x07, vga_video_port_reg);	/* Overflow */
	outb_p(vga_state.Overflow, vga_video_port_val);
	outb_p(0x10, vga_video_port_reg);	/* StartVertRetrace */
	outb_p(vga_state.StartVertRetrace, vga_video_port_val);
	outb_p(0x11, vga_video_port_reg);	/* EndVertRetrace */
	outb_p(vga_state.EndVertRetrace, vga_video_port_val);
	outb_p(0x17, vga_video_port_reg);	/* ModeControl */
	outb_p(vga_state.ModeControl, vga_video_port_val);
	/* ClockingMode */
	vga_wseq(state->vgabase, VGA_SEQ_CLOCK_MODE, vga_state.ClockingMode);

	/* restore index/control registers */
	vga_w(state->vgabase, VGA_SEQ_I, vga_state.SeqCtrlIndex);
	outb_p(vga_state.CrtCtrlIndex, vga_video_port_reg);
	raw_spin_unlock_irq(&vga_lock);
}