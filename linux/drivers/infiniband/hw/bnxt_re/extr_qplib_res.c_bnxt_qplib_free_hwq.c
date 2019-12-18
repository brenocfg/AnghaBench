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
struct pci_dev {int dummy; } ;
struct bnxt_qplib_hwq {int level; int is_user; scalar_t__ cp_bit; scalar_t__ cons; scalar_t__ prod; scalar_t__ element_size; scalar_t__ max_elements; int /*<<< orphan*/ * pbl; } ;

/* Variables and functions */
 int PBL_LVL_MAX ; 
 int /*<<< orphan*/  __free_pbl (struct pci_dev*,int /*<<< orphan*/ *,int) ; 

void bnxt_qplib_free_hwq(struct pci_dev *pdev, struct bnxt_qplib_hwq *hwq)
{
	int i;

	if (!hwq->max_elements)
		return;
	if (hwq->level >= PBL_LVL_MAX)
		return;

	for (i = 0; i < hwq->level + 1; i++) {
		if (i == hwq->level)
			__free_pbl(pdev, &hwq->pbl[i], hwq->is_user);
		else
			__free_pbl(pdev, &hwq->pbl[i], false);
	}

	hwq->level = PBL_LVL_MAX;
	hwq->max_elements = 0;
	hwq->element_size = 0;
	hwq->prod = 0;
	hwq->cons = 0;
	hwq->cp_bit = 0;
}