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
struct rvt_dev_info {int /*<<< orphan*/  n_cqs_lock; int /*<<< orphan*/  n_cqs_allocated; } ;
struct rvt_cq {int /*<<< orphan*/  queue; TYPE_1__* ip; int /*<<< orphan*/  comptask; struct rvt_dev_info* rdi; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 struct rvt_cq* ibcq_to_rvtcq (struct ib_cq*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_release_mmap_info ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void rvt_destroy_cq(struct ib_cq *ibcq, struct ib_udata *udata)
{
	struct rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	struct rvt_dev_info *rdi = cq->rdi;

	flush_work(&cq->comptask);
	spin_lock_irq(&rdi->n_cqs_lock);
	rdi->n_cqs_allocated--;
	spin_unlock_irq(&rdi->n_cqs_lock);
	if (cq->ip)
		kref_put(&cq->ip->ref, rvt_release_mmap_info);
	else
		vfree(cq->queue);
}