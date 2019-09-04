#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kone_mouse_event {int event; int /*<<< orphan*/  value; } ;
struct kone_device {int /*<<< orphan*/  actual_dpi; int /*<<< orphan*/  actual_profile; TYPE_1__* profiles; } ;
struct TYPE_2__ {int /*<<< orphan*/  startup_dpi; } ;

/* Variables and functions */
#define  kone_mouse_event_osd_dpi 131 
#define  kone_mouse_event_osd_profile 130 
#define  kone_mouse_event_switch_dpi 129 
#define  kone_mouse_event_switch_profile 128 

__attribute__((used)) static void kone_keep_values_up_to_date(struct kone_device *kone,
		struct kone_mouse_event const *event)
{
	switch (event->event) {
	case kone_mouse_event_switch_profile:
		kone->actual_dpi = kone->profiles[event->value - 1].
				startup_dpi;
	case kone_mouse_event_osd_profile:
		kone->actual_profile = event->value;
		break;
	case kone_mouse_event_switch_dpi:
	case kone_mouse_event_osd_dpi:
		kone->actual_dpi = event->value;
		break;
	}
}