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
struct mei_txe_hw {int /*<<< orphan*/  intr_cause; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HISR_INT_2_STS ; 
 int /*<<< orphan*/  HISR_REG ; 
 int /*<<< orphan*/  TXE_INTR_OUT_DB_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mei_txe_aliveness_set_sync (struct mei_device*,int) ; 
 int mei_txe_br_reg_read (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_br_reg_write (struct mei_txe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mei_txe_input_ready_interrupt_enable (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_intr_enable (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_output_ready_set (struct mei_txe_hw*) ; 
 int /*<<< orphan*/  mei_txe_readiness_set_host_rdy (struct mei_device*) ; 
 int mei_txe_readiness_wait (struct mei_device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_txe_hw_start(struct mei_device *dev)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);
	int ret;

	u32 hisr;

	/* bring back interrupts */
	mei_txe_intr_enable(dev);

	ret = mei_txe_readiness_wait(dev);
	if (ret < 0) {
		dev_err(dev->dev, "waiting for readiness failed\n");
		return ret;
	}

	/*
	 * If HISR.INT2_STS interrupt status bit is set then clear it.
	 */
	hisr = mei_txe_br_reg_read(hw, HISR_REG);
	if (hisr & HISR_INT_2_STS)
		mei_txe_br_reg_write(hw, HISR_REG, HISR_INT_2_STS);

	/* Clear the interrupt cause of OutputDoorbell */
	clear_bit(TXE_INTR_OUT_DB_BIT, &hw->intr_cause);

	ret = mei_txe_aliveness_set_sync(dev, 1);
	if (ret < 0) {
		dev_err(dev->dev, "wait for aliveness failed ... bailing out\n");
		return ret;
	}

	pm_runtime_set_active(dev->dev);

	/* enable input ready interrupts:
	 * SEC_IPC_HOST_INT_MASK.IPC_INPUT_READY_INT_MASK
	 */
	mei_txe_input_ready_interrupt_enable(dev);


	/*  Set the SICR_SEC_IPC_OUTPUT_STATUS.IPC_OUTPUT_READY bit */
	mei_txe_output_ready_set(hw);

	/* Set bit SICR_HOST_IPC_READINESS.HOST_RDY
	 */
	mei_txe_readiness_set_host_rdy(dev);

	return 0;
}