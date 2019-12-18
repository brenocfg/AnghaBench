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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  targ_id ;
struct esas2r_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ TS_LUN_CHANGE ; 
 scalar_t__ TS_NOT_PRESENT ; 
 scalar_t__ TS_PRESENT ; 
 int /*<<< orphan*/  esas2r_queue_fw_event (struct esas2r_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fw_event_lun_change ; 
 int /*<<< orphan*/  fw_event_not_present ; 
 int /*<<< orphan*/  fw_event_present ; 

void esas2r_target_state_changed(struct esas2r_adapter *a, u16 targ_id,
				 u8 state)
{
	if (state == TS_LUN_CHANGE)
		esas2r_queue_fw_event(a, fw_event_lun_change, &targ_id,
				      sizeof(targ_id));
	else if (state == TS_PRESENT)
		esas2r_queue_fw_event(a, fw_event_present, &targ_id,
				      sizeof(targ_id));
	else if (state == TS_NOT_PRESENT)
		esas2r_queue_fw_event(a, fw_event_not_present, &targ_id,
				      sizeof(targ_id));
}