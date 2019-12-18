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
typedef  int u8 ;
struct iwl_mvm_vif {int low_latency; int low_latency_actual; } ;
typedef  enum iwl_mvm_low_latency_cause { ____Placeholder_iwl_mvm_low_latency_cause } iwl_mvm_low_latency_cause ;

/* Variables and functions */
 int LOW_LATENCY_DEBUGFS_FORCE ; 
 int LOW_LATENCY_DEBUGFS_FORCE_ENABLE ; 

__attribute__((used)) static inline
void iwl_mvm_vif_set_low_latency(struct iwl_mvm_vif *mvmvif, bool set,
				 enum iwl_mvm_low_latency_cause cause)
{
	u8 new_state;

	if (set)
		mvmvif->low_latency |= cause;
	else
		mvmvif->low_latency &= ~cause;

	/*
	 * if LOW_LATENCY_DEBUGFS_FORCE_ENABLE is enabled no changes are
	 * allowed to actual mode.
	 */
	if (mvmvif->low_latency & LOW_LATENCY_DEBUGFS_FORCE_ENABLE &&
	    cause != LOW_LATENCY_DEBUGFS_FORCE_ENABLE)
		return;

	if (cause == LOW_LATENCY_DEBUGFS_FORCE_ENABLE && set)
		/*
		 * We enter force state
		 */
		new_state = !!(mvmvif->low_latency &
			       LOW_LATENCY_DEBUGFS_FORCE);
	else
		/*
		 * Check if any other one set low latency
		 */
		new_state = !!(mvmvif->low_latency &
				  ~(LOW_LATENCY_DEBUGFS_FORCE_ENABLE |
				    LOW_LATENCY_DEBUGFS_FORCE));

	mvmvif->low_latency_actual = new_state;
}