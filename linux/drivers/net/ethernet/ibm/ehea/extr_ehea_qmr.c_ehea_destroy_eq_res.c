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
typedef  scalar_t__ u64 ;
struct ehea_eq {int /*<<< orphan*/  hw_queue; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  fw_handle; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ H_SUCCESS ; 
 scalar_t__ ehea_h_free_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_queue_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ehea_eq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u64 ehea_destroy_eq_res(struct ehea_eq *eq, u64 force)
{
	u64 hret;
	unsigned long flags;

	spin_lock_irqsave(&eq->spinlock, flags);

	hret = ehea_h_free_resource(eq->adapter->handle, eq->fw_handle, force);
	spin_unlock_irqrestore(&eq->spinlock, flags);

	if (hret != H_SUCCESS)
		return hret;

	hw_queue_dtor(&eq->hw_queue);
	kfree(eq);

	return hret;
}