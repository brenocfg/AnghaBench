#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vc_data {int vc_npar; scalar_t__ vc_priv; int* vc_par; int vc_decscnm; int vc_decom; int vc_decawm; int vc_report_mouse; int vc_deccm; int vc_disp_ctrl; int vc_decim; int /*<<< orphan*/  vc_screenbuf_size; int /*<<< orphan*/  vc_rows; } ;

/* Variables and functions */
 scalar_t__ EPdec ; 
 int /*<<< orphan*/  clr_kbd (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decarm ; 
 int /*<<< orphan*/  decckm ; 
 int /*<<< orphan*/  deccolm ; 
 int /*<<< orphan*/  gotoxay (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invert_screen (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lnm ; 
 int /*<<< orphan*/  set_kbd (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_attr (struct vc_data*) ; 
 int /*<<< orphan*/  vc_resize (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_mode(struct vc_data *vc, int on_off)
{
	int i;

	for (i = 0; i <= vc->vc_npar; i++)
		if (vc->vc_priv == EPdec) {
			switch(vc->vc_par[i]) {	/* DEC private modes set/reset */
			case 1:			/* Cursor keys send ^[Ox/^[[x */
				if (on_off)
					set_kbd(vc, decckm);
				else
					clr_kbd(vc, decckm);
				break;
			case 3:	/* 80/132 mode switch unimplemented */
#if 0
				vc_resize(deccolm ? 132 : 80, vc->vc_rows);
				/* this alone does not suffice; some user mode
				   utility has to change the hardware regs */
#endif
				break;
			case 5:			/* Inverted screen on/off */
				if (vc->vc_decscnm != on_off) {
					vc->vc_decscnm = on_off;
					invert_screen(vc, 0, vc->vc_screenbuf_size, 0);
					update_attr(vc);
				}
				break;
			case 6:			/* Origin relative/absolute */
				vc->vc_decom = on_off;
				gotoxay(vc, 0, 0);
				break;
			case 7:			/* Autowrap on/off */
				vc->vc_decawm = on_off;
				break;
			case 8:			/* Autorepeat on/off */
				if (on_off)
					set_kbd(vc, decarm);
				else
					clr_kbd(vc, decarm);
				break;
			case 9:
				vc->vc_report_mouse = on_off ? 1 : 0;
				break;
			case 25:		/* Cursor on/off */
				vc->vc_deccm = on_off;
				break;
			case 1000:
				vc->vc_report_mouse = on_off ? 2 : 0;
				break;
			}
		} else {
			switch(vc->vc_par[i]) {	/* ANSI modes set/reset */
			case 3:			/* Monitor (display ctrls) */
				vc->vc_disp_ctrl = on_off;
				break;
			case 4:			/* Insert Mode on/off */
				vc->vc_decim = on_off;
				break;
			case 20:		/* Lf, Enter == CrLf/Lf */
				if (on_off)
					set_kbd(vc, lnm);
				else
					clr_kbd(vc, lnm);
				break;
			}
		}
}