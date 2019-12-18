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
typedef  int u8 ;
struct hidpp_device {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 scalar_t__ BTN_MISC ; 
 scalar_t__ BTN_MOUSE ; 
 int EINVAL ; 
 int HIDPP_SUB_ID_MOUSE_EXTRA_BTNS ; 
 int REPORT_ID_HIDPP_SHORT ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidpp10_extra_mouse_buttons_raw_event(struct hidpp_device *hidpp,
				    u8 *data, int size)
{
	int i;

	if (!hidpp->input)
		return -EINVAL;

	if (size < 7)
		return 0;

	if (data[0] != REPORT_ID_HIDPP_SHORT ||
	    data[2] != HIDPP_SUB_ID_MOUSE_EXTRA_BTNS)
		return 0;

	/*
	 * Buttons are either delivered through the regular mouse report *or*
	 * through the extra buttons report. At least for button 6 how it is
	 * delivered differs per receiver firmware version. Even receivers with
	 * the same usb-id show different behavior, so we handle both cases.
	 */
	for (i = 0; i < 8; i++)
		input_report_key(hidpp->input, BTN_MOUSE + i,
				 (data[3] & (1 << i)));

	/* Some mice report events on button 9+, use BTN_MISC */
	for (i = 0; i < 8; i++)
		input_report_key(hidpp->input, BTN_MISC + i,
				 (data[4] & (1 << i)));

	input_sync(hidpp->input);
	return 1;
}