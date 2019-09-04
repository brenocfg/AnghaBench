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
struct input_dev {int dummy; } ;
struct hidpp_device {int quirks; } ;

/* Variables and functions */
 int HIDPP_QUIRK_CLASS_M560 ; 
 int HIDPP_QUIRK_CLASS_WTP ; 
 int /*<<< orphan*/  m560_populate_input (struct hidpp_device*,struct input_dev*,int) ; 
 int /*<<< orphan*/  wtp_populate_input (struct hidpp_device*,struct input_dev*,int) ; 

__attribute__((used)) static void hidpp_populate_input(struct hidpp_device *hidpp,
		struct input_dev *input, bool origin_is_hid_core)
{
	if (hidpp->quirks & HIDPP_QUIRK_CLASS_WTP)
		wtp_populate_input(hidpp, input, origin_is_hid_core);
	else if (hidpp->quirks & HIDPP_QUIRK_CLASS_M560)
		m560_populate_input(hidpp, input, origin_is_hid_core);
}