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
typedef  scalar_t__ u32 ;
struct vnic_rq {int /*<<< orphan*/  index; } ;
struct vnic_cq {scalar_t__ tobe_rx_coal_timeval; scalar_t__ cur_rx_coal_timeval; } ;
struct enic {int /*<<< orphan*/ * intr; struct vnic_cq* cq; } ;

/* Variables and functions */
 size_t enic_cq_rq (struct enic*,int /*<<< orphan*/ ) ; 
 unsigned int enic_msix_rq_intr (struct enic*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnic_intr_coalescing_timer_set (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void enic_set_int_moderation(struct enic *enic, struct vnic_rq *rq)
{
	unsigned int intr = enic_msix_rq_intr(enic, rq->index);
	struct vnic_cq *cq = &enic->cq[enic_cq_rq(enic, rq->index)];
	u32 timer = cq->tobe_rx_coal_timeval;

	if (cq->tobe_rx_coal_timeval != cq->cur_rx_coal_timeval) {
		vnic_intr_coalescing_timer_set(&enic->intr[intr], timer);
		cq->cur_rx_coal_timeval = cq->tobe_rx_coal_timeval;
	}
}