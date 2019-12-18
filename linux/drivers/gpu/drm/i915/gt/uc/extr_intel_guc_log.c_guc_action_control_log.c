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
typedef  scalar_t__ u32 ;
struct intel_guc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_LOG_CONTROL_DEFAULT_LOGGING ; 
 scalar_t__ GUC_LOG_CONTROL_LOGGING_ENABLED ; 
 scalar_t__ GUC_LOG_CONTROL_VERBOSITY_SHIFT ; 
 scalar_t__ GUC_LOG_VERBOSITY_MAX ; 
 scalar_t__ INTEL_GUC_ACTION_UK_LOG_ENABLE_LOGGING ; 
 int intel_guc_send (struct intel_guc*,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int guc_action_control_log(struct intel_guc *guc, bool enable,
				  bool default_logging, u32 verbosity)
{
	u32 action[] = {
		INTEL_GUC_ACTION_UK_LOG_ENABLE_LOGGING,
		(enable ? GUC_LOG_CONTROL_LOGGING_ENABLED : 0) |
		(verbosity << GUC_LOG_CONTROL_VERBOSITY_SHIFT) |
		(default_logging ? GUC_LOG_CONTROL_DEFAULT_LOGGING : 0)
	};

	GEM_BUG_ON(verbosity > GUC_LOG_VERBOSITY_MAX);

	return intel_guc_send(guc, action, ARRAY_SIZE(action));
}