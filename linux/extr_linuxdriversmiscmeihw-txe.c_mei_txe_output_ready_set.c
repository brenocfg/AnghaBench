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
struct mei_txe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_IPC_OUTPUT_STATUS_RDY ; 
 int /*<<< orphan*/  SICR_SEC_IPC_OUTPUT_STATUS_REG ; 
 int /*<<< orphan*/  mei_txe_br_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mei_txe_output_ready_set(struct mei_txe_hw *hw)
{
	mei_txe_br_reg_write(hw,
			SICR_SEC_IPC_OUTPUT_STATUS_REG,
			SEC_IPC_OUTPUT_STATUS_RDY);
}