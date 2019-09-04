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
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  edac_dbg (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  pnd2_printk (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void pnd2_unregister_mci(struct mem_ctl_info *mci)
{
	if (unlikely(!mci || !mci->pvt_info)) {
		pnd2_printk(KERN_ERR, "Couldn't find mci handler\n");
		return;
	}

	/* Remove MC sysfs nodes */
	edac_mc_del_mc(NULL);
	edac_dbg(1, "%s: free mci struct\n", mci->ctl_name);
	edac_mc_free(mci);
}