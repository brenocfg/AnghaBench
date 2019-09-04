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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct xive_q {int /*<<< orphan*/  count; scalar_t__ msk; int /*<<< orphan*/  qpage; } ;
struct kvmppc_xive_vcpu {struct xive_q* queues; int /*<<< orphan*/  valid; } ;
struct TYPE_2__ {struct kvmppc_xive_vcpu* xive_vcpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ XIVE_Q_GAP ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int xive_try_pick_queue(struct kvm_vcpu *vcpu, u8 prio)
{
	struct kvmppc_xive_vcpu *xc = vcpu->arch.xive_vcpu;
	struct xive_q *q;
	u32 max;

	if (WARN_ON(!xc))
		return -ENXIO;
	if (!xc->valid)
		return -ENXIO;

	q = &xc->queues[prio];
	if (WARN_ON(!q->qpage))
		return -ENXIO;

	/* Calculate max number of interrupts in that queue. */
	max = (q->msk + 1) - XIVE_Q_GAP;
	return atomic_add_unless(&q->count, 1, max) ? 0 : -EBUSY;
}