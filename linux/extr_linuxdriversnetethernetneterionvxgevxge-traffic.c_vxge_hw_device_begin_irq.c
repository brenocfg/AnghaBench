#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  vpath_alarms; } ;
struct TYPE_6__ {int /*<<< orphan*/  not_traffic_intr_cnt; int /*<<< orphan*/  traffic_intr_cnt; int /*<<< orphan*/  total_intr_cnt; } ;
struct TYPE_8__ {TYPE_3__ sw_dev_err_stats; TYPE_2__ sw_dev_info_stats; } ;
struct __vxge_hw_device {int vpaths_deployed; int /*<<< orphan*/ * virtual_paths; TYPE_4__ stats; TYPE_1__* common_reg; } ;
typedef  enum vxge_hw_status { ____Placeholder_vxge_hw_status } vxge_hw_status ;
struct TYPE_5__ {int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  titan_general_int_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_VPID ; 
 scalar_t__ VXGE_HW_ALL_FOXES ; 
 int VXGE_HW_ERR_CRITICAL ; 
 int VXGE_HW_ERR_SLOT_FREEZE ; 
 int VXGE_HW_ERR_WRONG_IRQ ; 
 int /*<<< orphan*/  VXGE_HW_EVENT_SLOT_FREEZE ; 
 int VXGE_HW_MAX_VIRTUAL_PATHS ; 
 int VXGE_HW_OK ; 
 int VXGE_HW_SET_LEVEL (int,int) ; 
 scalar_t__ VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_ALARM_INT ; 
 scalar_t__ VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_TRAFFIC_INT (scalar_t__) ; 
 int /*<<< orphan*/  __vxge_hw_device_handle_error (struct __vxge_hw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __vxge_hw_vpath_alarm_process (int /*<<< orphan*/ *,int) ; 
 scalar_t__ readq (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int vxge_mBIT (int) ; 

enum vxge_hw_status vxge_hw_device_begin_irq(struct __vxge_hw_device *hldev,
					     u32 skip_alarms, u64 *reason)
{
	u32 i;
	u64 val64;
	u64 adapter_status;
	u64 vpath_mask;
	enum vxge_hw_status ret = VXGE_HW_OK;

	val64 = readq(&hldev->common_reg->titan_general_int_status);

	if (unlikely(!val64)) {
		/* not Titan interrupt	*/
		*reason	= 0;
		ret = VXGE_HW_ERR_WRONG_IRQ;
		goto exit;
	}

	if (unlikely(val64 == VXGE_HW_ALL_FOXES)) {

		adapter_status = readq(&hldev->common_reg->adapter_status);

		if (adapter_status == VXGE_HW_ALL_FOXES) {

			__vxge_hw_device_handle_error(hldev,
				NULL_VPID, VXGE_HW_EVENT_SLOT_FREEZE);
			*reason	= 0;
			ret = VXGE_HW_ERR_SLOT_FREEZE;
			goto exit;
		}
	}

	hldev->stats.sw_dev_info_stats.total_intr_cnt++;

	*reason	= val64;

	vpath_mask = hldev->vpaths_deployed >>
				(64 - VXGE_HW_MAX_VIRTUAL_PATHS);

	if (val64 &
	    VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_TRAFFIC_INT(vpath_mask)) {
		hldev->stats.sw_dev_info_stats.traffic_intr_cnt++;

		return VXGE_HW_OK;
	}

	hldev->stats.sw_dev_info_stats.not_traffic_intr_cnt++;

	if (unlikely(val64 &
			VXGE_HW_TITAN_GENERAL_INT_STATUS_VPATH_ALARM_INT)) {

		enum vxge_hw_status error_level = VXGE_HW_OK;

		hldev->stats.sw_dev_err_stats.vpath_alarms++;

		for (i = 0; i < VXGE_HW_MAX_VIRTUAL_PATHS; i++) {

			if (!(hldev->vpaths_deployed & vxge_mBIT(i)))
				continue;

			ret = __vxge_hw_vpath_alarm_process(
				&hldev->virtual_paths[i], skip_alarms);

			error_level = VXGE_HW_SET_LEVEL(ret, error_level);

			if (unlikely((ret == VXGE_HW_ERR_CRITICAL) ||
				(ret == VXGE_HW_ERR_SLOT_FREEZE)))
				break;
		}

		ret = error_level;
	}
exit:
	return ret;
}