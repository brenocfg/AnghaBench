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
struct hns_roce_srq {int dummy; } ;
struct hns_roce_cq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hns_roce_v2_cq_clean (struct hns_roce_cq*,int /*<<< orphan*/ ,struct hns_roce_srq*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns_roce_v2_cq_clean(struct hns_roce_cq *hr_cq, u32 qpn,
				 struct hns_roce_srq *srq)
{
	spin_lock_irq(&hr_cq->lock);
	__hns_roce_v2_cq_clean(hr_cq, qpn, srq);
	spin_unlock_irq(&hr_cq->lock);
}