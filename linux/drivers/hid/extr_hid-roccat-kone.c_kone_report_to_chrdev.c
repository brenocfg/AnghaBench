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
typedef  int /*<<< orphan*/  uint8_t ;
struct kone_roccat_report {int event; int /*<<< orphan*/  key; int /*<<< orphan*/  value; } ;
struct kone_mouse_event {int event; int /*<<< orphan*/  macro_key; int /*<<< orphan*/  value; } ;
struct kone_device {int /*<<< orphan*/  chrdev_minor; int /*<<< orphan*/  actual_profile; } ;

/* Variables and functions */
 int /*<<< orphan*/  kone_keystroke_action_press ; 
#define  kone_mouse_event_call_overlong_macro 133 
#define  kone_mouse_event_multimedia 132 
#define  kone_mouse_event_osd_dpi 131 
#define  kone_mouse_event_osd_profile 130 
#define  kone_mouse_event_switch_dpi 129 
#define  kone_mouse_event_switch_profile 128 
 int /*<<< orphan*/  roccat_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kone_report_to_chrdev(struct kone_device const *kone,
		struct kone_mouse_event const *event)
{
	struct kone_roccat_report roccat_report;

	switch (event->event) {
	case kone_mouse_event_switch_profile:
	case kone_mouse_event_switch_dpi:
	case kone_mouse_event_osd_profile:
	case kone_mouse_event_osd_dpi:
		roccat_report.event = event->event;
		roccat_report.value = event->value;
		roccat_report.key = 0;
		roccat_report_event(kone->chrdev_minor,
				(uint8_t *)&roccat_report);
		break;
	case kone_mouse_event_call_overlong_macro:
	case kone_mouse_event_multimedia:
		if (event->value == kone_keystroke_action_press) {
			roccat_report.event = event->event;
			roccat_report.value = kone->actual_profile;
			roccat_report.key = event->macro_key;
			roccat_report_event(kone->chrdev_minor,
					(uint8_t *)&roccat_report);
		}
		break;
	}

}