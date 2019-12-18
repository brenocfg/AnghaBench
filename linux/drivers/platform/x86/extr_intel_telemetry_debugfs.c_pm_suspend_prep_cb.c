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
struct telemetry_evtlog {int dummy; } ;
struct telemetry_debugfs_conf {int /*<<< orphan*/  s0ix_deep_res_id; int /*<<< orphan*/  s0ix_shlw_res_id; int /*<<< orphan*/  s0ix_deep_occ_id; int /*<<< orphan*/  s0ix_shlw_occ_id; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  TELEM_CHECK_AND_PARSE_CTRS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TELEM_IOSS ; 
 int TELEM_MAX_OS_ALLOCATED_EVENTS ; 
 struct telemetry_debugfs_conf* debugfs_conf ; 
 int /*<<< orphan*/  suspend_deep_ctr_temp ; 
 int /*<<< orphan*/  suspend_deep_res_temp ; 
 int suspend_prep_ok ; 
 int /*<<< orphan*/  suspend_shlw_ctr_temp ; 
 int /*<<< orphan*/  suspend_shlw_res_temp ; 
 int telemetry_raw_read_eventlog (int /*<<< orphan*/ ,struct telemetry_evtlog*,int) ; 

__attribute__((used)) static int pm_suspend_prep_cb(void)
{
	struct telemetry_evtlog evtlog[TELEM_MAX_OS_ALLOCATED_EVENTS];
	struct telemetry_debugfs_conf *conf = debugfs_conf;
	int ret, index;

	ret = telemetry_raw_read_eventlog(TELEM_IOSS, evtlog,
			TELEM_MAX_OS_ALLOCATED_EVENTS);
	if (ret < 0) {
		suspend_prep_ok = 0;
		goto out;
	}

	for (index = 0; index < ret; index++) {

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_occ_id,
					   suspend_shlw_ctr_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctr_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_shlw_res_id,
					   suspend_shlw_res_temp);

		TELEM_CHECK_AND_PARSE_CTRS(conf->s0ix_deep_res_id,
					   suspend_deep_res_temp);
	}
	suspend_prep_ok = 1;
out:
	return NOTIFY_OK;
}