#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; int /*<<< orphan*/  data; int /*<<< orphan*/  rtype; } ;
struct TYPE_4__ {TYPE_1__ output; } ;
struct uhid_event {TYPE_2__ u; int /*<<< orphan*/  type; } ;
struct uhid_device {int /*<<< orphan*/  qlock; } ;
struct hid_device {struct uhid_device* driver_data; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HID_FEATURE_REPORT 129 
#define  HID_OUTPUT_REPORT 128 
 size_t UHID_DATA_MAX ; 
 int /*<<< orphan*/  UHID_FEATURE_REPORT ; 
 int /*<<< orphan*/  UHID_OUTPUT ; 
 int /*<<< orphan*/  UHID_OUTPUT_REPORT ; 
 struct uhid_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uhid_queue (struct uhid_device*,struct uhid_event*) ; 

__attribute__((used)) static int uhid_hid_output_raw(struct hid_device *hid, __u8 *buf, size_t count,
			       unsigned char report_type)
{
	struct uhid_device *uhid = hid->driver_data;
	__u8 rtype;
	unsigned long flags;
	struct uhid_event *ev;

	switch (report_type) {
	case HID_FEATURE_REPORT:
		rtype = UHID_FEATURE_REPORT;
		break;
	case HID_OUTPUT_REPORT:
		rtype = UHID_OUTPUT_REPORT;
		break;
	default:
		return -EINVAL;
	}

	if (count < 1 || count > UHID_DATA_MAX)
		return -EINVAL;

	ev = kzalloc(sizeof(*ev), GFP_KERNEL);
	if (!ev)
		return -ENOMEM;

	ev->type = UHID_OUTPUT;
	ev->u.output.size = count;
	ev->u.output.rtype = rtype;
	memcpy(ev->u.output.data, buf, count);

	spin_lock_irqsave(&uhid->qlock, flags);
	uhid_queue(uhid, ev);
	spin_unlock_irqrestore(&uhid->qlock, flags);

	return count;
}