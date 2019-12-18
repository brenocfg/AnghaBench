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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct telemetry_evtlog {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  deep_res; int /*<<< orphan*/  deep_ctr; int /*<<< orphan*/  shlw_res; int /*<<< orphan*/  shlw_ctr; } ;
struct telemetry_debugfs_conf {TYPE_1__ suspend_stats; int /*<<< orphan*/  s0ix_deep_res_id; int /*<<< orphan*/  s0ix_shlw_res_id; int /*<<< orphan*/  s0ix_deep_occ_id; int /*<<< orphan*/  s0ix_shlw_occ_id; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  PMC_GCR_TELEM_DEEP_S0IX_REG ; 
 int /*<<< orphan*/  PMC_GCR_TELEM_SHLW_S0IX_REG ; 
 int /*<<< orphan*/  TELEM_CHECK_AND_PARSE_CTRS (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TELEM_IOSS ; 
 int TELEM_MAX_OS_ALLOCATED_EVENTS ; 
 struct telemetry_debugfs_conf* debugfs_conf ; 
 int intel_pmc_gcr_read64 (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ suspend_deep_ctr_temp ; 
 scalar_t__ suspend_deep_res_temp ; 
 scalar_t__ suspend_prep_ok ; 
 scalar_t__ suspend_shlw_ctr_temp ; 
 scalar_t__ suspend_shlw_res_temp ; 
 int telemetry_raw_read_eventlog (int /*<<< orphan*/ ,struct telemetry_evtlog*,int) ; 

__attribute__((used)) static int pm_suspend_exit_cb(void)
{
	struct telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	static u32 suspend_shlw_ctr_exit, suspend_deep_ctr_exit;
	static u64 suspend_shlw_res_exit, suspend_deep_res_exit;
	struct telemetry_debugfs_conf *conf = debugfs_conf;
	int ret, index;

	if (!suspend_prep_ok)
		goto out;

	ret = telemetry_raw_read_eventlog(TELEM_IOSS, evtlog,
					  TELEM_MAX_OS_ALLOCATED_EVENTS);
	if (ret < 0)
		goto out;

	for (index = 0; index < ret; index++) {
		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_occ_id,
					   suspend_shlw_ctr_exit);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctr_exit);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_res_id,
					   suspend_shlw_res_exit);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_res_id,
					   suspend_deep_res_exit);
	}

	if ((suspend_shlw_ctr_exit < suspend_shlw_ctr_temp) ||
	    (suspend_deep_ctr_exit < suspend_deep_ctr_temp) ||
	    (suspend_shlw_res_exit < suspend_shlw_res_temp) ||
	    (suspend_deep_res_exit < suspend_deep_res_temp)) {
		pr_err("Wrong s0ix counters detected\n");
		goto out;
	}

	/*
	 * Due to some design limitations in the firmware, sometimes the
	 * counters do not get updated by the time we reach here. As a
	 * workaround, we try to see if this was a genuine case of sleep
	 * failure or not by cross-checking from PMC GCR registers directly.
	 */
	if (suspend_shlw_ctr_exit == suspend_shlw_ctr_temp &&
	    suspend_deep_ctr_exit == suspend_deep_ctr_temp) {
		ret = intel_pmc_gcr_read64(PMC_GCR_TELEM_SHLW_S0IX_REG,
					  &suspend_shlw_res_exit);
		if (ret < 0)
			goto out;

		ret = intel_pmc_gcr_read64(PMC_GCR_TELEM_DEEP_S0IX_REG,
					  &suspend_deep_res_exit);
		if (ret < 0)
			goto out;

		if (suspend_shlw_res_exit > suspend_shlw_res_temp)
			suspend_shlw_ctr_exit++;

		if (suspend_deep_res_exit > suspend_deep_res_temp)
			suspend_deep_ctr_exit++;
	}

	suspend_shlw_ctr_exit -= suspend_shlw_ctr_temp;
	suspend_deep_ctr_exit -= suspend_deep_ctr_temp;
	suspend_shlw_res_exit -= suspend_shlw_res_temp;
	suspend_deep_res_exit -= suspend_deep_res_temp;

	if (suspend_shlw_ctr_exit != 0) {
		conf->suspend_stats.shlw_ctr +=
		suspend_shlw_ctr_exit;

		conf->suspend_stats.shlw_res +=
		suspend_shlw_res_exit;
	}

	if (suspend_deep_ctr_exit != 0) {
		conf->suspend_stats.deep_ctr +=
		suspend_deep_ctr_exit;

		conf->suspend_stats.deep_res +=
		suspend_deep_res_exit;
	}

out:
	suspend_prep_ok = 0;
	return NOTIFY_OK;
}