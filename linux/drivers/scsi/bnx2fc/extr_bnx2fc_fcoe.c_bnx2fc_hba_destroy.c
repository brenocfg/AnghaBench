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
struct bnx2fc_hba {struct bnx2fc_hba* tgt_ofld_list; int /*<<< orphan*/ * cmd_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnx2fc_cmd_mgr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnx2fc_unbind_pcidev (struct bnx2fc_hba*) ; 
 int /*<<< orphan*/  kfree (struct bnx2fc_hba*) ; 

__attribute__((used)) static void bnx2fc_hba_destroy(struct bnx2fc_hba *hba)
{
	/* Free the command manager */
	if (hba->cmd_mgr) {
		bnx2fc_cmd_mgr_free(hba->cmd_mgr);
		hba->cmd_mgr = NULL;
	}
	kfree(hba->tgt_ofld_list);
	bnx2fc_unbind_pcidev(hba);
	kfree(hba);
}