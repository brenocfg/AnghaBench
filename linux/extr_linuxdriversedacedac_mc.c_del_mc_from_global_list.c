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
struct mem_ctl_info {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mc_devices ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int del_mc_from_global_list(struct mem_ctl_info *mci)
{
	list_del_rcu(&mci->link);

	/* these are for safe removal of devices from global list while
	 * NMI handlers may be traversing list
	 */
	synchronize_rcu();
	INIT_LIST_HEAD(&mci->link);

	return list_empty(&mc_devices);
}