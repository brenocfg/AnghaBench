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
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HHISR_REG ; 
 int /*<<< orphan*/  HISR_INT_STS_MSK ; 
 int /*<<< orphan*/  HISR_REG ; 
 int /*<<< orphan*/  IPC_HHIER_MSK ; 
 int /*<<< orphan*/  SEC_IPC_HOST_INT_STATUS_PENDING ; 
 int /*<<< orphan*/  SEC_IPC_HOST_INT_STATUS_REG ; 
 int /*<<< orphan*/  mei_txe_br_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_sec_reg_write_silent (struct mei_txe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static inline void mei_txe_intr_clear(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_reg_write_silent(hw, SEC_IPC_HOST_INT_STATUS_REG,
		SEC_IPC_HOST_INT_STATUS_PENDING);
	mei_txe_br_reg_write(hw, HISR_REG, HISR_INT_STS_MSK);
	mei_txe_br_reg_write(hw, HHISR_REG, IPC_HHIER_MSK);
}