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
typedef  int /*<<< orphan*/  u32 ;
struct fm10k_swapi_error {int /*<<< orphan*/  status; int /*<<< orphan*/  ffu; int /*<<< orphan*/  nexthop; int /*<<< orphan*/  mac; } ;
struct fm10k_mbx_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  ffu; int /*<<< orphan*/  nexthop; int /*<<< orphan*/  mac; } ;
struct fm10k_hw {TYPE_1__ swapi; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  err_msg ;

/* Variables and functions */
 size_t FM10K_PF_ATTR_ID_ERR ; 
 int /*<<< orphan*/  fm10k_record_global_table_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_tlv_attr_get_le_struct (int /*<<< orphan*/ *,struct fm10k_swapi_error*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

s32 fm10k_msg_err_pf(struct fm10k_hw *hw, u32 **results,
		     struct fm10k_mbx_info *mbx)
{
	struct fm10k_swapi_error err_msg;
	s32 err;

	/* extract structure from message */
	err = fm10k_tlv_attr_get_le_struct(results[FM10K_PF_ATTR_ID_ERR],
					   &err_msg, sizeof(err_msg));
	if (err)
		return err;

	/* record table status */
	fm10k_record_global_table_data(&err_msg.mac, &hw->swapi.mac);
	fm10k_record_global_table_data(&err_msg.nexthop, &hw->swapi.nexthop);
	fm10k_record_global_table_data(&err_msg.ffu, &hw->swapi.ffu);

	/* record SW API status value */
	hw->swapi.status = le32_to_cpu(err_msg.status);

	return 0;
}