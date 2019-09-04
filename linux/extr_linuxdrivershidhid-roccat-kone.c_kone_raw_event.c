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
typedef  int /*<<< orphan*/  u8 ;
struct kone_mouse_event {int /*<<< orphan*/  tilt; } ;
struct TYPE_2__ {int /*<<< orphan*/  tilt; } ;
struct kone_device {scalar_t__ roccat_claimed; TYPE_1__ last_mouse_event; } ;
struct hid_report {int dummy; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 struct kone_device* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  kone_keep_values_up_to_date (struct kone_device*,struct kone_mouse_event*) ; 
 int /*<<< orphan*/  kone_report_to_chrdev (struct kone_device*,struct kone_mouse_event*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct kone_mouse_event*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kone_raw_event(struct hid_device *hdev, struct hid_report *report,
		u8 *data, int size)
{
	struct kone_device *kone = hid_get_drvdata(hdev);
	struct kone_mouse_event *event = (struct kone_mouse_event *)data;

	/* keyboard events are always processed by default handler */
	if (size != sizeof(struct kone_mouse_event))
		return 0;

	if (kone == NULL)
		return 0;

	/*
	 * Firmware 1.38 introduced new behaviour for tilt and special buttons.
	 * Pressed button is reported in each movement event.
	 * Workaround sends only one event per press.
	 */
	if (memcmp(&kone->last_mouse_event.tilt, &event->tilt, 5))
		memcpy(&kone->last_mouse_event, event,
				sizeof(struct kone_mouse_event));
	else
		memset(&event->tilt, 0, 5);

	kone_keep_values_up_to_date(kone, event);

	if (kone->roccat_claimed)
		kone_report_to_chrdev(kone, event);

	return 0; /* always do further processing */
}