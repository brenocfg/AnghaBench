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
typedef  scalar_t__ u32 ;
struct intel_uncore {int dummy; } ;
struct intel_guc {int dummy; } ;
struct TYPE_2__ {struct intel_uncore* uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,scalar_t__,scalar_t__) ; 
 int EIO ; 
 scalar_t__ GUC_POWER_D1 ; 
 scalar_t__ INTEL_GUC_ACTION_ENTER_S_STATE ; 
 int /*<<< orphan*/  INTEL_GUC_SLEEP_STATE_INVALID_MASK ; 
 scalar_t__ INTEL_GUC_SLEEP_STATE_SUCCESS ; 
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 int __intel_wait_for_register (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 int intel_guc_send (struct intel_guc*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int intel_guc_suspend(struct intel_guc *guc)
{
	struct intel_uncore *uncore = guc_to_gt(guc)->uncore;
	int ret;
	u32 status;
	u32 action[] = {
		INTEL_GUC_ACTION_ENTER_S_STATE,
		GUC_POWER_D1, /* any value greater than GUC_POWER_D0 */
	};

	/*
	 * The ENTER_S_STATE action queues the save/restore operation in GuC FW
	 * and then returns, so waiting on the H2G is not enough to guarantee
	 * GuC is done. When all the processing is done, GuC writes
	 * INTEL_GUC_SLEEP_STATE_SUCCESS to scratch register 14, so we can poll
	 * on that. Note that GuC does not ensure that the value in the register
	 * is different from INTEL_GUC_SLEEP_STATE_SUCCESS while the action is
	 * in progress so we need to take care of that ourselves as well.
	 */

	intel_uncore_write(uncore, SOFT_SCRATCH(14),
			   INTEL_GUC_SLEEP_STATE_INVALID_MASK);

	ret = intel_guc_send(guc, action, ARRAY_SIZE(action));
	if (ret)
		return ret;

	ret = __intel_wait_for_register(uncore, SOFT_SCRATCH(14),
					INTEL_GUC_SLEEP_STATE_INVALID_MASK,
					0, 0, 10, &status);
	if (ret)
		return ret;

	if (status != INTEL_GUC_SLEEP_STATE_SUCCESS) {
		DRM_ERROR("GuC failed to change sleep state. "
			  "action=0x%x, err=%u\n",
			  action[0], status);
		return -EIO;
	}

	return 0;
}