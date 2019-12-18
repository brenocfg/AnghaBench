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
typedef  union iwl_dbg_tlv_tp_data {int dummy; } iwl_dbg_tlv_tp_data ;
struct iwl_fw_runtime {int dummy; } ;
typedef  enum iwl_fw_ini_time_point { ____Placeholder_iwl_fw_ini_time_point } iwl_fw_ini_time_point ;

/* Variables and functions */

void iwl_dbg_tlv_time_point(struct iwl_fw_runtime *fwrt,
			    enum iwl_fw_ini_time_point tp_id,
			    union iwl_dbg_tlv_tp_data *tp_data)
{
	/* will be used later */
}