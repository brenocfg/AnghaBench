#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct qed_spq_entry {int dummy; } ;
struct qed_spq {int /*<<< orphan*/  chain; int /*<<< orphan*/  p_phys; scalar_t__ p_virt; } ;
struct qed_hwfn {struct qed_spq* p_spq; TYPE_2__* cdev; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_spq*) ; 
 int /*<<< orphan*/  qed_chain_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int qed_chain_get_capacity (int /*<<< orphan*/ *) ; 

void qed_spq_free(struct qed_hwfn *p_hwfn)
{
	struct qed_spq *p_spq = p_hwfn->p_spq;
	u32 capacity;

	if (!p_spq)
		return;

	if (p_spq->p_virt) {
		capacity = qed_chain_get_capacity(&p_spq->chain);
		dma_free_coherent(&p_hwfn->cdev->pdev->dev,
				  capacity *
				  sizeof(struct qed_spq_entry),
				  p_spq->p_virt, p_spq->p_phys);
	}

	qed_chain_free(p_hwfn->cdev, &p_spq->chain);
	kfree(p_spq);
	p_hwfn->p_spq = NULL;
}