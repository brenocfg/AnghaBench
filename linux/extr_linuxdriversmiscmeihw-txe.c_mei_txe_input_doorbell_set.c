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
struct mei_txe_hw {int /*<<< orphan*/  intr_cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_IPC_INPUT_DOORBELL_REG ; 
 int /*<<< orphan*/  TXE_INTR_IN_READY_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_txe_sec_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mei_txe_input_doorbell_set(struct mei_txe_hw *hw)
{
	/* Clear the interrupt cause */
	clear_bit(TXE_INTR_IN_READY_BIT, &hw->intr_cause);
	mei_txe_sec_reg_write(hw, SEC_IPC_INPUT_DOORBELL_REG, 1);
}