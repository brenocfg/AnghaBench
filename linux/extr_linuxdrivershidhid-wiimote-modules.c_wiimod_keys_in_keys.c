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
struct wiimote_data {int /*<<< orphan*/  input; } ;
typedef  int __u8 ;

/* Variables and functions */
 size_t WIIPROTO_KEY_A ; 
 size_t WIIPROTO_KEY_B ; 
 size_t WIIPROTO_KEY_DOWN ; 
 size_t WIIPROTO_KEY_HOME ; 
 size_t WIIPROTO_KEY_LEFT ; 
 size_t WIIPROTO_KEY_MINUS ; 
 size_t WIIPROTO_KEY_ONE ; 
 size_t WIIPROTO_KEY_PLUS ; 
 size_t WIIPROTO_KEY_RIGHT ; 
 size_t WIIPROTO_KEY_TWO ; 
 size_t WIIPROTO_KEY_UP ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wiimod_keys_map ; 

__attribute__((used)) static void wiimod_keys_in_keys(struct wiimote_data *wdata, const __u8 *keys)
{
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_LEFT],
							!!(keys[0] & 0x01));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_RIGHT],
							!!(keys[0] & 0x02));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_DOWN],
							!!(keys[0] & 0x04));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_UP],
							!!(keys[0] & 0x08));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_PLUS],
							!!(keys[0] & 0x10));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_TWO],
							!!(keys[1] & 0x01));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_ONE],
							!!(keys[1] & 0x02));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_B],
							!!(keys[1] & 0x04));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_A],
							!!(keys[1] & 0x08));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_MINUS],
							!!(keys[1] & 0x10));
	input_report_key(wdata->input, wiimod_keys_map[WIIPROTO_KEY_HOME],
							!!(keys[1] & 0x80));
	input_sync(wdata->input);
}