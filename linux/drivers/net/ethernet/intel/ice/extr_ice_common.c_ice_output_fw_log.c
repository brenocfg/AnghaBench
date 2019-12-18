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
typedef  int /*<<< orphan*/  u8 ;
struct ice_hw {int dummy; } ;
struct ice_aq_desc {int /*<<< orphan*/  datalen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_DBG_FW_LOG ; 
 int /*<<< orphan*/  ice_debug (struct ice_hw*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ice_debug_array (struct ice_hw*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

void ice_output_fw_log(struct ice_hw *hw, struct ice_aq_desc *desc, void *buf)
{
	ice_debug(hw, ICE_DBG_FW_LOG, "[ FW Log Msg Start ]\n");
	ice_debug_array(hw, ICE_DBG_FW_LOG, 16, 1, (u8 *)buf,
			le16_to_cpu(desc->datalen));
	ice_debug(hw, ICE_DBG_FW_LOG, "[ FW Log Msg End ]\n");
}