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
struct dmar_drhd_unit {int /*<<< orphan*/  list; scalar_t__ include_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmar_drhd_units ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dmar_register_drhd_unit(struct dmar_drhd_unit *drhd)
{
	/*
	 * add INCLUDE_ALL at the tail, so scan the list will find it at
	 * the very end.
	 */
	if (drhd->include_all)
		list_add_tail_rcu(&drhd->list, &dmar_drhd_units);
	else
		list_add_rcu(&drhd->list, &dmar_drhd_units);
}