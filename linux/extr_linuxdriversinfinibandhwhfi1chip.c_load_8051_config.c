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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCMD_LOAD_CONFIG_DATA ; 
 int HCMD_SUCCESS ; 
 int LOAD_DATA_DATA_SHIFT ; 
 int LOAD_DATA_FIELD_ID_SHIFT ; 
 int LOAD_DATA_LANE_ID_SHIFT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int,int,int) ; 
 int do_8051_command (struct hfi1_devdata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int load_8051_config(struct hfi1_devdata *dd, u8 field_id,
		     u8 lane_id, u32 config_data)
{
	u64 data;
	int ret;

	data = (u64)field_id << LOAD_DATA_FIELD_ID_SHIFT
		| (u64)lane_id << LOAD_DATA_LANE_ID_SHIFT
		| (u64)config_data << LOAD_DATA_DATA_SHIFT;
	ret = do_8051_command(dd, HCMD_LOAD_CONFIG_DATA, data, NULL);
	if (ret != HCMD_SUCCESS) {
		dd_dev_err(dd,
			   "load 8051 config: field id %d, lane %d, err %d\n",
			   (int)field_id, (int)lane_id, ret);
	}
	return ret;
}