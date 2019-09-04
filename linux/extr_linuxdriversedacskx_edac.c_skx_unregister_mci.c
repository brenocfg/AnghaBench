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
struct skx_imc {int /*<<< orphan*/  mc; struct mem_ctl_info* mci; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skx_unregister_mci(struct skx_imc *imc)
{
	struct mem_ctl_info *mci = imc->mci;

	if (!mci)
		return;

	edac_dbg(0, "MC%d: mci = %p\n", imc->mc, mci);

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(mci->pdev);

	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	kfree(mci->ctl_name);
	edac_mc_free(mci);
}