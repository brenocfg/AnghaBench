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
struct qed_hwfn {TYPE_1__* p_consq; int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  qed_chain_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qed_consq_free(struct qed_hwfn *p_hwfn)
{
	if (!p_hwfn->p_consq)
		return;

	qed_chain_free(p_hwfn->cdev, &p_hwfn->p_consq->chain);

	kfree(p_hwfn->p_consq);
	p_hwfn->p_consq = NULL;
}