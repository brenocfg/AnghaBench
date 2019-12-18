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
typedef  int u32 ;
struct qman_portal {int dummy; } ;
struct qman_fq {scalar_t__ state; int fqid; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  QMAN_FQ_STATE_VDQCR ; 
 int QMAN_VOLATILE_FLAG_FINISH ; 
 int QMAN_VOLATILE_FLAG_WAIT ; 
 int QMAN_VOLATILE_FLAG_WAIT_INT ; 
 int QM_VDQCR_FQID_MASK ; 
 int /*<<< orphan*/  affine_queue ; 
 scalar_t__ fq_isset (struct qman_fq*,int /*<<< orphan*/ ) ; 
 scalar_t__ qman_fq_state_parked ; 
 scalar_t__ qman_fq_state_retired ; 
 int set_vdqcr (struct qman_portal**,struct qman_fq*,int) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int wait_vdqcr_start (struct qman_portal**,struct qman_fq*,int,int) ; 

int qman_volatile_dequeue(struct qman_fq *fq, u32 flags, u32 vdqcr)
{
	struct qman_portal *p;
	int ret;

	if (fq->state != qman_fq_state_parked &&
	    fq->state != qman_fq_state_retired)
		return -EINVAL;
	if (vdqcr & QM_VDQCR_FQID_MASK)
		return -EINVAL;
	if (fq_isset(fq, QMAN_FQ_STATE_VDQCR))
		return -EBUSY;
	vdqcr = (vdqcr & ~QM_VDQCR_FQID_MASK) | fq->fqid;
	if (flags & QMAN_VOLATILE_FLAG_WAIT)
		ret = wait_vdqcr_start(&p, fq, vdqcr, flags);
	else
		ret = set_vdqcr(&p, fq, vdqcr);
	if (ret)
		return ret;
	/* VDQCR is set */
	if (flags & QMAN_VOLATILE_FLAG_FINISH) {
		if (flags & QMAN_VOLATILE_FLAG_WAIT_INT)
			/*
			 * NB: don't propagate any error - the caller wouldn't
			 * know whether the VDQCR was issued or not. A signal
			 * could arrive after returning anyway, so the caller
			 * can check signal_pending() if that's an issue.
			 */
			wait_event_interruptible(affine_queue,
				!fq_isset(fq, QMAN_FQ_STATE_VDQCR));
		else
			wait_event(affine_queue,
				!fq_isset(fq, QMAN_FQ_STATE_VDQCR));
	}
	return 0;
}