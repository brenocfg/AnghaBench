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
struct rmid_read {int first; int /*<<< orphan*/  evtid; struct rdt_domain* d; } ;
struct rdt_domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QOS_L3_MBM_LOCAL_EVENT_ID ; 
 int /*<<< orphan*/  QOS_L3_MBM_TOTAL_EVENT_ID ; 
 int /*<<< orphan*/  __mon_event_count (int,struct rmid_read*) ; 
 int /*<<< orphan*/  is_mba_sc (int /*<<< orphan*/ *) ; 
 scalar_t__ is_mbm_local_enabled () ; 
 scalar_t__ is_mbm_total_enabled () ; 
 int /*<<< orphan*/  mbm_bw_count (int,struct rmid_read*) ; 

__attribute__((used)) static void mbm_update(struct rdt_domain *d, int rmid)
{
	struct rmid_read rr;

	rr.first = false;
	rr.d = d;

	/*
	 * This is protected from concurrent reads from user
	 * as both the user and we hold the global mutex.
	 */
	if (is_mbm_total_enabled()) {
		rr.evtid = QOS_L3_MBM_TOTAL_EVENT_ID;
		__mon_event_count(rmid, &rr);
	}
	if (is_mbm_local_enabled()) {
		rr.evtid = QOS_L3_MBM_LOCAL_EVENT_ID;

		/*
		 * Call the MBA software controller only for the
		 * control groups and when user has enabled
		 * the software controller explicitly.
		 */
		if (!is_mba_sc(NULL))
			__mon_event_count(rmid, &rr);
		else
			mbm_bw_count(rmid, &rr);
	}
}