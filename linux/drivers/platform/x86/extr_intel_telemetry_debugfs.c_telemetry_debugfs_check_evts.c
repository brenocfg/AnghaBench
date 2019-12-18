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
struct TYPE_2__ {scalar_t__ pss_idle_evts; scalar_t__ pcs_idle_blkd_evts; scalar_t__ pcs_s0ix_blkd_evts; scalar_t__ pss_ltr_evts; scalar_t__ pss_wakeup_evts; scalar_t__ ioss_d0ix_evts; scalar_t__ ioss_pg_evts; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ TELEM_IOSS_DX_D0IX_EVTS ; 
 scalar_t__ TELEM_IOSS_PG_EVTS ; 
 scalar_t__ TELEM_PSS_IDLE_BLOCKED_EVTS ; 
 scalar_t__ TELEM_PSS_IDLE_EVTS ; 
 scalar_t__ TELEM_PSS_LTR_BLOCKING_EVTS ; 
 scalar_t__ TELEM_PSS_S0IX_BLOCKED_EVTS ; 
 scalar_t__ TELEM_PSS_S0IX_WAKEUP_EVTS ; 
 TYPE_1__* debugfs_conf ; 

__attribute__((used)) static int telemetry_debugfs_check_evts(void)
{
	if ((debugfs_conf->pss_idle_evts > TELEM_PSS_IDLE_EVTS) ||
	    (debugfs_conf->pcs_idle_blkd_evts > TELEM_PSS_IDLE_BLOCKED_EVTS) ||
	    (debugfs_conf->pcs_s0ix_blkd_evts > TELEM_PSS_S0IX_BLOCKED_EVTS) ||
	    (debugfs_conf->pss_ltr_evts > TELEM_PSS_LTR_BLOCKING_EVTS) ||
	    (debugfs_conf->pss_wakeup_evts > TELEM_PSS_S0IX_WAKEUP_EVTS) ||
	    (debugfs_conf->ioss_d0ix_evts > TELEM_IOSS_DX_D0IX_EVTS) ||
	    (debugfs_conf->ioss_pg_evts > TELEM_IOSS_PG_EVTS))
		return -EINVAL;

	return 0;
}