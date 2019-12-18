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
struct koneplus_mouse_report_button {int /*<<< orphan*/  data1; int /*<<< orphan*/  type; } ;
struct koneplus_device {int dummy; } ;

/* Variables and functions */
#define  KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE 129 
#define  KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON 128 
 int /*<<< orphan*/  koneplus_profile_activated (struct koneplus_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void koneplus_keep_values_up_to_date(struct koneplus_device *koneplus,
		u8 const *data)
{
	struct koneplus_mouse_report_button const *button_report;

	switch (data[0]) {
	case KONEPLUS_MOUSE_REPORT_NUMBER_BUTTON:
		button_report = (struct koneplus_mouse_report_button const *)data;
		switch (button_report->type) {
		case KONEPLUS_MOUSE_REPORT_BUTTON_TYPE_PROFILE:
			koneplus_profile_activated(koneplus, button_report->data1 - 1);
			break;
		}
		break;
	}
}