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
typedef  int u32 ;
struct mei_txe_hw {int dummy; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int SEC_IPC_INPUT_STATUS_RDY ; 
 int /*<<< orphan*/  SEC_IPC_INPUT_STATUS_REG ; 
 int mei_txe_sec_reg_read (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static bool mei_txe_is_input_ready(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);
	u32 status;

	status = mei_txe_sec_reg_read(hw, SEC_IPC_INPUT_STATUS_REG);
	return !!(SEC_IPC_INPUT_STATUS_RDY & status);
}