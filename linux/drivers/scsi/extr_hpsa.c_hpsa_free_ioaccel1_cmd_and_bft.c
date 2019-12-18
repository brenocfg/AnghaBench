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
struct ctlr_info {int nr_cmds; int /*<<< orphan*/ * ioaccel1_blockFetchTable; scalar_t__ ioaccel_cmd_pool_dhandle; int /*<<< orphan*/ * ioaccel_cmd_pool; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void hpsa_free_ioaccel1_cmd_and_bft(struct ctlr_info *h)
{
	if (h->ioaccel_cmd_pool) {
		pci_free_consistent(h->pdev,
			h->nr_cmds * sizeof(*h->ioaccel_cmd_pool),
			h->ioaccel_cmd_pool,
			h->ioaccel_cmd_pool_dhandle);
		h->ioaccel_cmd_pool = NULL;
		h->ioaccel_cmd_pool_dhandle = 0;
	}
	kfree(h->ioaccel1_blockFetchTable);
	h->ioaccel1_blockFetchTable = NULL;
}