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
struct TYPE_3__ {int port_num; } ;
struct ib_event {TYPE_1__ element; int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;
struct hns_roce_dev {int active; int is_reset; int /*<<< orphan*/  ib_dev; } ;
struct hnae3_handle {TYPE_2__* pdev; scalar_t__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 

__attribute__((used)) static int hns_roce_hw_v2_reset_notify_down(struct hnae3_handle *handle)
{
	struct hns_roce_dev *hr_dev = (struct hns_roce_dev *)handle->priv;
	struct ib_event event;

	if (!hr_dev) {
		dev_err(&handle->pdev->dev,
			"Input parameter handle->priv is NULL!\n");
		return -EINVAL;
	}

	hr_dev->active = false;
	hr_dev->is_reset = true;

	event.event = IB_EVENT_DEVICE_FATAL;
	event.device = &hr_dev->ib_dev;
	event.element.port_num = 1;
	ib_dispatch_event(&event);

	return 0;
}