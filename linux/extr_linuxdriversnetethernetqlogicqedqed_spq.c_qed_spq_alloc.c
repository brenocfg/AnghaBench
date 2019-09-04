#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct slow_path_element {int dummy; } ;
struct qed_spq_entry {int dummy; } ;
struct qed_spq {int /*<<< orphan*/  chain; int /*<<< orphan*/  p_phys; struct qed_spq_entry* p_virt; } ;
struct qed_hwfn {TYPE_2__* cdev; struct qed_spq* p_spq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_SINGLE ; 
 int /*<<< orphan*/  QED_CHAIN_USE_TO_PRODUCE ; 
 struct qed_spq_entry* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_spq*) ; 
 struct qed_spq* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qed_chain_alloc (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_chain_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int qed_chain_get_capacity (int /*<<< orphan*/ *) ; 

int qed_spq_alloc(struct qed_hwfn *p_hwfn)
{
	struct qed_spq_entry *p_virt = NULL;
	struct qed_spq *p_spq = NULL;
	dma_addr_t p_phys = 0;
	u32 capacity;

	/* SPQ struct */
	p_spq = kzalloc(sizeof(struct qed_spq), GFP_KERNEL);
	if (!p_spq)
		return -ENOMEM;

	/* SPQ ring  */
	if (qed_chain_alloc(p_hwfn->cdev,
			    QED_CHAIN_USE_TO_PRODUCE,
			    QED_CHAIN_MODE_SINGLE,
			    QED_CHAIN_CNT_TYPE_U16,
			    0,   /* N/A when the mode is SINGLE */
			    sizeof(struct slow_path_element),
			    &p_spq->chain, NULL))
		goto spq_allocate_fail;

	/* allocate and fill the SPQ elements (incl. ramrod data list) */
	capacity = qed_chain_get_capacity(&p_spq->chain);
	p_virt = dma_alloc_coherent(&p_hwfn->cdev->pdev->dev,
				    capacity * sizeof(struct qed_spq_entry),
				    &p_phys, GFP_KERNEL);
	if (!p_virt)
		goto spq_allocate_fail;

	p_spq->p_virt = p_virt;
	p_spq->p_phys = p_phys;
	p_hwfn->p_spq = p_spq;

	return 0;

spq_allocate_fail:
	qed_chain_free(p_hwfn->cdev, &p_spq->chain);
	kfree(p_spq);
	return -ENOMEM;
}