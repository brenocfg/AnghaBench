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
struct smu7_hwmgr {int active_auto_throttle_sources; } ;
struct pp_hwmgr {scalar_t__ backend; } ;
typedef  int PHM_AutoThrottleSource ;

/* Variables and functions */
 int /*<<< orphan*/  smu7_set_dpm_event_sources (struct pp_hwmgr*,int) ; 

__attribute__((used)) static int smu7_enable_auto_throttle_source(struct pp_hwmgr *hwmgr,
		PHM_AutoThrottleSource source)
{
	struct smu7_hwmgr *data = (struct smu7_hwmgr *)(hwmgr->backend);

	if (!(data->active_auto_throttle_sources & (1 << source))) {
		data->active_auto_throttle_sources |= 1 << source;
		smu7_set_dpm_event_sources(hwmgr, data->active_auto_throttle_sources);
	}
	return 0;
}