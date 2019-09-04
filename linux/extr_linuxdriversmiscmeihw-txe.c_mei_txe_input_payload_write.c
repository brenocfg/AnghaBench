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
typedef  int /*<<< orphan*/  u32 ;
struct mei_txe_hw {int dummy; } ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SEC_IPC_INPUT_PAYLOAD_REG ; 
 int /*<<< orphan*/  mei_txe_sec_reg_write (struct mei_txe_hw*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static void mei_txe_input_payload_write(struct mei_device *dev,
			unsigned long idx, u32 value)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_reg_write(hw, SEC_IPC_INPUT_PAYLOAD_REG +
			(idx * sizeof(u32)), value);
}