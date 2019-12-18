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
struct qman_portal {int /*<<< orphan*/  mr_work; int /*<<< orphan*/  p; int /*<<< orphan*/  congestion_work; } ;

/* Variables and functions */
 int QM_PIRQ_CSCI ; 
 int QM_PIRQ_EQRI ; 
 int QM_PIRQ_MRI ; 
 int /*<<< orphan*/  affine_queue ; 
 int /*<<< orphan*/  qm_eqcr_cce_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qm_eqcr_set_ithresh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qm_portal_wq ; 
 int /*<<< orphan*/  qman_p_irqsource_remove (struct qman_portal*,int) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 __poll_portal_slow(struct qman_portal *p, u32 is)
{
	if (is & QM_PIRQ_CSCI) {
		qman_p_irqsource_remove(p, QM_PIRQ_CSCI);
		queue_work_on(smp_processor_id(), qm_portal_wq,
			      &p->congestion_work);
	}

	if (is & QM_PIRQ_EQRI) {
		qm_eqcr_cce_update(&p->p);
		qm_eqcr_set_ithresh(&p->p, 0);
		wake_up(&affine_queue);
	}

	if (is & QM_PIRQ_MRI) {
		qman_p_irqsource_remove(p, QM_PIRQ_MRI);
		queue_work_on(smp_processor_id(), qm_portal_wq,
			      &p->mr_work);
	}

	return is;
}