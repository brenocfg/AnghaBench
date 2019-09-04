#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev_flags; } ;
struct TYPE_6__ {TYPE_2__ start; } ;
struct uhid_event {TYPE_3__ u; int /*<<< orphan*/  type; } ;
struct uhid_device {int /*<<< orphan*/  qlock; } ;
struct hid_device {TYPE_1__* report_enum; struct uhid_device* driver_data; } ;
struct TYPE_4__ {scalar_t__ numbered; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HID_FEATURE_REPORT ; 
 size_t HID_INPUT_REPORT ; 
 size_t HID_OUTPUT_REPORT ; 
 int /*<<< orphan*/  UHID_DEV_NUMBERED_FEATURE_REPORTS ; 
 int /*<<< orphan*/  UHID_DEV_NUMBERED_INPUT_REPORTS ; 
 int /*<<< orphan*/  UHID_DEV_NUMBERED_OUTPUT_REPORTS ; 
 int /*<<< orphan*/  UHID_START ; 
 struct uhid_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uhid_queue (struct uhid_device*,struct uhid_event*) ; 

__attribute__((used)) static int uhid_hid_start(struct hid_device *hid)
{
	struct uhid_device *uhid = hid->driver_data;
	struct uhid_event *ev;
	unsigned long flags;

	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;

	ev->type = UHID_START;

	if (hid->report_enum[HID_FEATURE_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_FEATURE_REPORTS;
	if (hid->report_enum[HID_OUTPUT_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_OUTPUT_REPORTS;
	if (hid->report_enum[HID_INPUT_REPORT].numbered)
		ev->u.start.dev_flags |= UHID_DEV_NUMBERED_INPUT_REPORTS;

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	return 0;
}