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
struct TYPE_4__ {int port_num; } ;
struct ib_event {TYPE_2__ element; int /*<<< orphan*/ * device; int /*<<< orphan*/  event; } ;
struct hns_roce_dev {int is_reset; int active; int dis_db; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_3__ {scalar_t__ instance_state; int /*<<< orphan*/  state; int /*<<< orphan*/  reset_state; } ;
struct hnae3_handle {scalar_t__ priv; TYPE_1__ rinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS_ROCE_RST_DIRECT_RETURN ; 
 scalar_t__ HNS_ROCE_STATE_INITED ; 
 int /*<<< orphan*/  HNS_ROCE_STATE_RST_DOWN ; 
 int /*<<< orphan*/  IB_EVENT_DEVICE_FATAL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_dispatch_event (struct ib_event*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hns_roce_hw_v2_reset_notify_down(struct hnae3_handle *handle)
{
	struct hns_roce_dev *hr_dev;
	struct ib_event event;

	if (handle->rinfo.instance_state != HNS_ROCE_STATE_INITED) {
		set_bit(HNS_ROCE_RST_DIRECT_RETURN, &handle->rinfo.state);
		return 0;
	}

	handle->rinfo.reset_state = HNS_ROCE_STATE_RST_DOWN;
	clear_bit(HNS_ROCE_RST_DIRECT_RETURN, &handle->rinfo.state);

	hr_dev = (struct hns_roce_dev *)handle->priv;
	if (!hr_dev)
		return 0;

	hr_dev->is_reset = true;
	hr_dev->active = false;
	hr_dev->dis_db = true;

	event.event = IB_EVENT_DEVICE_FATAL;
	event.device = &hr_dev->ib_dev;
	event.element.port_num = 1;
	ib_dispatch_event(&event);

	return 0;
}