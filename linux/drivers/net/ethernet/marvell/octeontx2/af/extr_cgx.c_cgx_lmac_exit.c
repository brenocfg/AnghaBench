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
struct lmac {struct lmac* name; } ;
struct cgx {int lmac_count; int /*<<< orphan*/  pdev; struct lmac** lmac_idmap; int /*<<< orphan*/ * cgx_cmd_workq; } ;

/* Variables and functions */
 scalar_t__ CGX_LMAC_FWI ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct lmac*) ; 
 int /*<<< orphan*/  kfree (struct lmac*) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int cgx_lmac_exit(struct cgx *cgx)
{
	struct lmac *lmac;
	int i;

	if (cgx->cgx_cmd_workq) {
		flush_workqueue(cgx->cgx_cmd_workq);
		destroy_workqueue(cgx->cgx_cmd_workq);
		cgx->cgx_cmd_workq = NULL;
	}

	/* Free all lmac related resources */
	for (i = 0; i < cgx->lmac_count; i++) {
		lmac = cgx->lmac_idmap[i];
		if (!lmac)
			continue;
		free_irq(pci_irq_vector(cgx->pdev, CGX_LMAC_FWI + i * 9), lmac);
		kfree(lmac->name);
		kfree(lmac);
	}

	return 0;
}