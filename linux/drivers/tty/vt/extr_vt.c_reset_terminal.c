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
struct vc_data {int vc_decawm; int* vc_tab_stop; int /*<<< orphan*/  vc_cur_blink_ms; int /*<<< orphan*/  vc_bell_duration; int /*<<< orphan*/  vc_bell_pitch; int /*<<< orphan*/  vc_s_complement_mask; int /*<<< orphan*/  vc_complement_mask; int /*<<< orphan*/  vc_cursor_type; int /*<<< orphan*/  vc_num; scalar_t__ vc_decim; int /*<<< orphan*/  vc_deccm; scalar_t__ vc_decom; scalar_t__ vc_decscnm; scalar_t__ vc_toggle_meta; scalar_t__ vc_disp_ctrl; scalar_t__ vc_utf_count; int /*<<< orphan*/  vc_utf; scalar_t__ vc_report_mouse; scalar_t__ vc_need_wrap; scalar_t__ vc_charset; int /*<<< orphan*/  vc_G1_charset; int /*<<< orphan*/  vc_G0_charset; int /*<<< orphan*/  vc_translate; int /*<<< orphan*/  vc_priv; int /*<<< orphan*/  vc_state; int /*<<< orphan*/  vc_rows; int /*<<< orphan*/  vc_bottom; scalar_t__ vc_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BELL_DURATION ; 
 int /*<<< orphan*/  DEFAULT_BELL_PITCH ; 
 int /*<<< orphan*/  DEFAULT_CURSOR_BLINK_MS ; 
 int /*<<< orphan*/  EPecma ; 
 int /*<<< orphan*/  ESnormal ; 
 int /*<<< orphan*/  GRAF_MAP ; 
 int /*<<< orphan*/  LAT1_MAP ; 
 int /*<<< orphan*/  csi_J (struct vc_data*,int) ; 
 int /*<<< orphan*/  cur_default ; 
 int /*<<< orphan*/  default_attr (struct vc_data*) ; 
 int /*<<< orphan*/  default_utf8 ; 
 int /*<<< orphan*/  global_cursor_default ; 
 int /*<<< orphan*/  gotoxy (struct vc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_cur (struct vc_data*) ; 
 int /*<<< orphan*/  set_translate (int /*<<< orphan*/ ,struct vc_data*) ; 
 int /*<<< orphan*/  update_attr (struct vc_data*) ; 
 int /*<<< orphan*/  vt_reset_keyboard (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_terminal(struct vc_data *vc, int do_clear)
{
	vc->vc_top		= 0;
	vc->vc_bottom		= vc->vc_rows;
	vc->vc_state		= ESnormal;
	vc->vc_priv		= EPecma;
	vc->vc_translate	= set_translate(LAT1_MAP, vc);
	vc->vc_G0_charset	= LAT1_MAP;
	vc->vc_G1_charset	= GRAF_MAP;
	vc->vc_charset		= 0;
	vc->vc_need_wrap	= 0;
	vc->vc_report_mouse	= 0;
	vc->vc_utf              = default_utf8;
	vc->vc_utf_count	= 0;

	vc->vc_disp_ctrl	= 0;
	vc->vc_toggle_meta	= 0;

	vc->vc_decscnm		= 0;
	vc->vc_decom		= 0;
	vc->vc_decawm		= 1;
	vc->vc_deccm		= global_cursor_default;
	vc->vc_decim		= 0;

	vt_reset_keyboard(vc->vc_num);

	vc->vc_cursor_type = cur_default;
	vc->vc_complement_mask = vc->vc_s_complement_mask;

	default_attr(vc);
	update_attr(vc);

	vc->vc_tab_stop[0]	=
	vc->vc_tab_stop[1]	=
	vc->vc_tab_stop[2]	=
	vc->vc_tab_stop[3]	=
	vc->vc_tab_stop[4]	=
	vc->vc_tab_stop[5]	=
	vc->vc_tab_stop[6]	=
	vc->vc_tab_stop[7]	= 0x01010101;

	vc->vc_bell_pitch = DEFAULT_BELL_PITCH;
	vc->vc_bell_duration = DEFAULT_BELL_DURATION;
	vc->vc_cur_blink_ms = DEFAULT_CURSOR_BLINK_MS;

	gotoxy(vc, 0, 0);
	save_cur(vc);
	if (do_clear)
	    csi_J(vc, 2);
}