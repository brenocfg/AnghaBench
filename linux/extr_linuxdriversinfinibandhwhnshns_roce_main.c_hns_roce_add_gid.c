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
typedef  scalar_t__ u8 ;
struct ib_gid_attr {scalar_t__ port_num; int /*<<< orphan*/  gid; int /*<<< orphan*/  index; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {scalar_t__ num_ports; } ;
struct hns_roce_dev {TYPE_2__ iboe; TYPE_1__* hw; TYPE_3__ caps; } ;
struct TYPE_4__ {int (* set_gid ) (struct hns_roce_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_gid_attr const*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct hns_roce_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_gid_attr const*) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hns_roce_add_gid(const struct ib_gid_attr *attr, void **context)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(attr->device);
	u8 port = attr->port_num - 1;
	unsigned long flags;
	int ret;

	if (port >= hr_dev->caps.num_ports)
		return -EINVAL;

	spin_lock_irqsave(&hr_dev->iboe.lock, flags);

	ret = hr_dev->hw->set_gid(hr_dev, port, attr->index, &attr->gid, attr);

	spin_unlock_irqrestore(&hr_dev->iboe.lock, flags);

	return ret;
}