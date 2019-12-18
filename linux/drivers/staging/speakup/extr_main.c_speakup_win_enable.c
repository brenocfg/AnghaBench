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
 int /*<<< orphan*/  MSG_NO_WINDOW ; 
 int /*<<< orphan*/  MSG_WINDOW_SILENCED ; 
 int /*<<< orphan*/  MSG_WINDOW_SILENCE_DISABLED ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 
 int win_enabled ; 
 int win_start ; 

__attribute__((used)) static void speakup_win_enable(struct vc_data *vc)
{
	if (win_start < 2) {
		synth_printf("%s\n", spk_msg_get(MSG_NO_WINDOW));
		return;
	}
	win_enabled ^= 1;
	if (win_enabled)
		synth_printf("%s\n", spk_msg_get(MSG_WINDOW_SILENCED));
	else
		synth_printf("%s\n", spk_msg_get(MSG_WINDOW_SILENCE_DISABLED));
}