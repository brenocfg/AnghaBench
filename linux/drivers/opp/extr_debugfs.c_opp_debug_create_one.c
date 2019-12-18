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
struct opp_table {struct dentry* dentry; } ;
struct dev_pm_opp {unsigned long rate; unsigned long clock_latency_ns; struct dentry* dentry; int /*<<< orphan*/  pstate; int /*<<< orphan*/  suspend; int /*<<< orphan*/  turbo; int /*<<< orphan*/  dynamic; int /*<<< orphan*/  available; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  S_IRUGO ; 
 unsigned long _get_opp_count (struct opp_table*) ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_ulong (char*,int /*<<< orphan*/ ,struct dentry*,unsigned long*) ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  opp_debug_create_supplies (struct dev_pm_opp*,struct opp_table*,struct dentry*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned long) ; 

void opp_debug_create_one(struct dev_pm_opp *opp, struct opp_table *opp_table)
{
	struct dentry *pdentry = opp_table->dentry;
	struct dentry *d;
	unsigned long id;
	char name[25];	/* 20 chars for 64 bit value + 5 (opp:\0) */

	/*
	 * Get directory name for OPP.
	 *
	 * - Normally rate is unique to each OPP, use it to get unique opp-name.
	 * - For some devices rate isn't available, use index instead.
	 */
	if (likely(opp->rate))
		id = opp->rate;
	else
		id = _get_opp_count(opp_table);

	snprintf(name, sizeof(name), "opp:%lu", id);

	/* Create per-opp directory */
	d = debugfs_create_dir(name, pdentry);

	debugfs_create_bool("available", S_IRUGO, d, &opp->available);
	debugfs_create_bool("dynamic", S_IRUGO, d, &opp->dynamic);
	debugfs_create_bool("turbo", S_IRUGO, d, &opp->turbo);
	debugfs_create_bool("suspend", S_IRUGO, d, &opp->suspend);
	debugfs_create_u32("performance_state", S_IRUGO, d, &opp->pstate);
	debugfs_create_ulong("rate_hz", S_IRUGO, d, &opp->rate);
	debugfs_create_ulong("clock_latency_ns", S_IRUGO, d,
			     &opp->clock_latency_ns);

	opp_debug_create_supplies(opp, opp_table, d);

	opp->dentry = d;
}