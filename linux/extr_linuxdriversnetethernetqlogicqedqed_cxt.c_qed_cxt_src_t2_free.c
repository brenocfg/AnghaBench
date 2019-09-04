#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct qed_hwfn {TYPE_2__* cdev; struct qed_cxt_mngr* p_cxt_mngr; } ;
struct qed_cxt_mngr {size_t t2_num_pages; TYPE_3__* t2; } ;
struct TYPE_6__ {int /*<<< orphan*/  p_phys; scalar_t__ p_virt; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 

__attribute__((used)) static void qed_cxt_src_t2_free(struct qed_hwfn *p_hwfn)
{
	struct qed_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	u32 i;

	if (!p_mngr->t2)
		return;

	for (i = 0; i < p_mngr->t2_num_pages; i++)
		if (p_mngr->t2[i].p_virt)
			dma_free_coherent(&p_hwfn->cdev->pdev->dev,
					  p_mngr->t2[i].size,
					  p_mngr->t2[i].p_virt,
					  p_mngr->t2[i].p_phys);

	kfree(p_mngr->t2);
	p_mngr->t2 = NULL;
}