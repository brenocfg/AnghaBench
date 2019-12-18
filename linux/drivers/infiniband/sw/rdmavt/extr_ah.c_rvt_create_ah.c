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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  (* notify_new_ah ) (int /*<<< orphan*/ ,struct rdma_ah_attr*,struct rvt_ah*) ;} ;
struct TYPE_4__ {scalar_t__ max_ah; } ;
struct TYPE_5__ {TYPE_1__ props; } ;
struct rvt_dev_info {scalar_t__ n_ahs_allocated; TYPE_3__ driver_f; int /*<<< orphan*/  n_ahs_lock; TYPE_2__ dparms; } ;
struct rvt_ah {int /*<<< orphan*/  attr; } ;
struct rdma_ah_attr {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_ah* ibah_to_rvtah (struct ib_ah*) ; 
 int /*<<< orphan*/  rdma_copy_ah_attr (int /*<<< orphan*/ *,struct rdma_ah_attr*) ; 
 scalar_t__ rvt_check_ah (int /*<<< orphan*/ ,struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct rdma_ah_attr*,struct rvt_ah*) ; 

int rvt_create_ah(struct ib_ah *ibah, struct rdma_ah_attr *ah_attr,
		  u32 create_flags, struct ib_udata *udata)
{
	struct rvt_ah *ah = ibah_to_rvtah(ibah);
	struct rvt_dev_info *dev = ib_to_rvt(ibah->device);
	unsigned long flags;

	if (rvt_check_ah(ibah->device, ah_attr))
		return -EINVAL;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	if (dev->n_ahs_allocated == dev->dparms.props.max_ah) {
		spin_unlock_irqrestore(&dev->n_ahs_lock, flags);
		return -ENOMEM;
	}

	dev->n_ahs_allocated++;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	rdma_copy_ah_attr(&ah->attr, ah_attr);

	if (dev->driver_f.notify_new_ah)
		dev->driver_f.notify_new_ah(ibah->device, ah_attr, ah);

	return 0;
}