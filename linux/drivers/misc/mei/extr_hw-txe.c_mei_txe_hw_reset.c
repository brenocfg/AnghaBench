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
typedef  scalar_t__ u32 ;
struct mei_txe_hw {scalar_t__ aliveness; } ;
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SEC_IPC_INPUT_DOORBELL_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mei_txe_aliveness_get (struct mei_device*) ; 
 scalar_t__ mei_txe_aliveness_poll (struct mei_device*,scalar_t__) ; 
 scalar_t__ mei_txe_aliveness_req_get (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_aliveness_set (struct mei_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_txe_intr_disable (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_readiness_clear (struct mei_device*) ; 
 int /*<<< orphan*/  mei_txe_sec_reg_read_silent (struct mei_txe_hw*,int /*<<< orphan*/ ) ; 
 struct mei_txe_hw* to_txe_hw (struct mei_device*) ; 

__attribute__((used)) static int mei_txe_hw_reset(struct mei_device *dev, bool intr_enable)
{
	struct mei_txe_hw *hw = to_txe_hw(dev);

	u32 aliveness_req;
	/*
	 * read input doorbell to ensure consistency between  Bridge and SeC
	 * return value might be garbage return
	 */
	(void)mei_txe_sec_reg_read_silent(hw, SEC_IPC_INPUT_DOORBELL_REG);

	aliveness_req = mei_txe_aliveness_req_get(dev);
	hw->aliveness = mei_txe_aliveness_get(dev);

	/* Disable interrupts in this stage we will poll */
	mei_txe_intr_disable(dev);

	/*
	 * If Aliveness Request and Aliveness Response are not equal then
	 * wait for them to be equal
	 * Since we might have interrupts disabled - poll for it
	 */
	if (aliveness_req != hw->aliveness)
		if (mei_txe_aliveness_poll(dev, aliveness_req) < 0) {
			dev_err(dev->dev, "wait for aliveness settle failed ... bailing out\n");
			return -EIO;
		}

	/*
	 * If Aliveness Request and Aliveness Response are set then clear them
	 */
	if (aliveness_req) {
		mei_txe_aliveness_set(dev, 0);
		if (mei_txe_aliveness_poll(dev, 0) < 0) {
			dev_err(dev->dev, "wait for aliveness failed ... bailing out\n");
			return -EIO;
		}
	}

	/*
	 * Set readiness RDY_CLR bit
	 */
	mei_txe_readiness_clear(dev);

	return 0;
}