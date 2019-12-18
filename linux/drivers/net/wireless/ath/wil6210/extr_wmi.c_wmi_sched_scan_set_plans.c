#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wmi_start_sched_scan_cmd {TYPE_1__* scan_plans; } ;
struct wil6210_priv {int dummy; } ;
struct cfg80211_sched_scan_plan {int /*<<< orphan*/  iterations; int /*<<< orphan*/  interval; } ;
struct TYPE_2__ {void* num_of_iterations; void* interval_sec; } ;

/* Variables and functions */
 int WMI_MAX_PLANS_NUM ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,int,int) ; 

__attribute__((used)) static void
wmi_sched_scan_set_plans(struct wil6210_priv *wil,
			 struct wmi_start_sched_scan_cmd *cmd,
			 struct cfg80211_sched_scan_plan *scan_plans,
			 int n_scan_plans)
{
	int i;

	if (n_scan_plans > WMI_MAX_PLANS_NUM) {
		wil_dbg_wmi(wil, "too many plans (%d), use first %d\n",
			    n_scan_plans, WMI_MAX_PLANS_NUM);
		n_scan_plans = WMI_MAX_PLANS_NUM;
	}

	for (i = 0; i < n_scan_plans; i++) {
		struct cfg80211_sched_scan_plan *cfg_plan = &scan_plans[i];

		cmd->scan_plans[i].interval_sec =
			cpu_to_le16(cfg_plan->interval);
		cmd->scan_plans[i].num_of_iterations =
			cpu_to_le16(cfg_plan->iterations);
	}
}