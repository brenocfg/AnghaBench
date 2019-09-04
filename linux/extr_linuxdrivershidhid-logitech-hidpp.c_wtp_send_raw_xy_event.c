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
struct wtp_data {int /*<<< orphan*/  input; } ;
struct hidpp_touchpad_raw_xy {int finger_count; scalar_t__ end_of_frame; int /*<<< orphan*/  button; int /*<<< orphan*/ * fingers; } ;
struct hidpp_device {int quirks; struct wtp_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  EV_KEY ; 
 int HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_sync_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wtp_touch_event (struct wtp_data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wtp_send_raw_xy_event(struct hidpp_device *hidpp,
		struct hidpp_touchpad_raw_xy *raw)
{
	struct wtp_data *wd = hidpp->private_data;
	int i;

	for (i = 0; i < 2; i++)
		wtp_touch_event(wd, &(raw->fingers[i]));

	if (raw->end_of_frame &&
	    !(hidpp->quirks & HIDPP_QUIRK_WTP_PHYSICAL_BUTTONS))
		input_event(wd->input, EV_KEY, BTN_LEFT, raw->button);

	if (raw->end_of_frame || raw->finger_count <= 2) {
		input_mt_sync_frame(wd->input);
		input_sync(wd->input);
	}
}