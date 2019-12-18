#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct telemetry_evtconfig {size_t* evtmap; int num_evts; int /*<<< orphan*/  period; } ;
struct TYPE_9__ {int ssram_evts_used; TYPE_3__* telem_evts; int /*<<< orphan*/  curr_period; } ;
struct TYPE_7__ {int ssram_evts_used; TYPE_1__* telem_evts; int /*<<< orphan*/  curr_period; } ;
struct TYPE_10__ {int /*<<< orphan*/  telem_lock; TYPE_4__ ioss_config; TYPE_2__ pss_config; } ;
struct TYPE_8__ {size_t evt_id; } ;
struct TYPE_6__ {size_t evt_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_5__* telm_conf ; 

__attribute__((used)) static int telemetry_plt_get_eventconfig(struct telemetry_evtconfig *pss_config,
					struct telemetry_evtconfig *ioss_config,
					int pss_len, int ioss_len)
{
	u32 *pss_evtmap, *ioss_evtmap;
	u32 index;

	pss_evtmap = pss_config->evtmap;
	ioss_evtmap = ioss_config->evtmap;

	mutex_lock(&(telm_conf->telem_lock));
	pss_config->num_evts = telm_conf->pss_config.ssram_evts_used;
	ioss_config->num_evts = telm_conf->ioss_config.ssram_evts_used;

	pss_config->period = telm_conf->pss_config.curr_period;
	ioss_config->period = telm_conf->ioss_config.curr_period;

	if ((pss_len < telm_conf->pss_config.ssram_evts_used) ||
	    (ioss_len < telm_conf->ioss_config.ssram_evts_used)) {
		mutex_unlock(&(telm_conf->telem_lock));
		return -EINVAL;
	}

	for (index = 0; index < telm_conf->pss_config.ssram_evts_used;
	     index++) {
		pss_evtmap[index] =
		telm_conf->pss_config.telem_evts[index].evt_id;
	}

	for (index = 0; index < telm_conf->ioss_config.ssram_evts_used;
	     index++) {
		ioss_evtmap[index] =
		telm_conf->ioss_config.telem_evts[index].evt_id;
	}

	mutex_unlock(&(telm_conf->telem_lock));
	return 0;
}