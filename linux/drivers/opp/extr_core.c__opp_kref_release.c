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
struct opp_table {int /*<<< orphan*/  head; } ;
struct dev_pm_opp {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPP_EVENT_REMOVE ; 
 int /*<<< orphan*/  _of_opp_free_required_opps (struct opp_table*,struct dev_pm_opp*) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dev_pm_opp*) ; 
 int /*<<< orphan*/  kfree (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opp_debug_remove_one (struct dev_pm_opp*) ; 

__attribute__((used)) static void _opp_kref_release(struct dev_pm_opp *opp,
			      struct opp_table *opp_table)
{
	/*
	 * Notify the changes in the availability of the operable
	 * frequency/voltage list.
	 */
	blocking_notifier_call_chain(&opp_table->head, OPP_EVENT_REMOVE, opp);
	_of_opp_free_required_opps(opp_table, opp);
	opp_debug_remove_one(opp);
	list_del(&opp->node);
	kfree(opp);
}