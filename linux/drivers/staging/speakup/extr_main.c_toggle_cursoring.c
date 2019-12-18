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
struct vc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ CT_Max ; 
 scalar_t__ MSG_CURSOR_MSGS_START ; 
 scalar_t__ cursor_track ; 
 scalar_t__ prev_cursor_track ; 
 scalar_t__ read_all_mode ; 
 int /*<<< orphan*/  spk_msg_get (scalar_t__) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void toggle_cursoring(struct vc_data *vc)
{
	if (cursor_track == read_all_mode)
		cursor_track = prev_cursor_track;
	if (++cursor_track >= CT_Max)
		cursor_track = 0;
	synth_printf("%s\n", spk_msg_get(MSG_CURSOR_MSGS_START + cursor_track));
}