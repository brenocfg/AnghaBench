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
typedef  int /*<<< orphan*/  u32 ;
struct rvt_dev_info {int /*<<< orphan*/  n_ahs_lock; int /*<<< orphan*/  n_ahs_allocated; } ;
struct rvt_ah {int /*<<< orphan*/  attr; } ;
struct ib_ah {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_ah* ibah_to_rvtah (struct ib_ah*) ; 
 int /*<<< orphan*/  rdma_destroy_ah_attr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rvt_destroy_ah(struct ib_ah *ibah, u32 destroy_flags)
{
	struct rvt_dev_info *dev = ib_to_rvt(ibah->device);
	struct rvt_ah *ah = ibah_to_rvtah(ibah);
	unsigned long flags;

	spin_lock_irqsave(&dev->n_ahs_lock, flags);
	dev->n_ahs_allocated--;
	spin_unlock_irqrestore(&dev->n_ahs_lock, flags);

	rdma_destroy_ah_attr(&ah->attr);
}