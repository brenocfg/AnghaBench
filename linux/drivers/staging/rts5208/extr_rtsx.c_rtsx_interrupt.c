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
struct rtsx_dev {int check_card_cd; scalar_t__ trans_state; int /*<<< orphan*/  reg_lock; scalar_t__ done; void* trans_result; struct rtsx_chip* chip; } ;
struct rtsx_chip {int int_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DATA_DONE_INT ; 
 int DELINK_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int NEED_COMPLETE_INT ; 
 int /*<<< orphan*/  RTSX_SET_DELINK (struct rtsx_chip*) ; 
 scalar_t__ STATE_TRANS_SG ; 
 int STATUS_FAIL ; 
 int TRANS_FAIL_INT ; 
 void* TRANS_NOT_READY ; 
 int TRANS_OK_INT ; 
 void* TRANS_RESULT_FAIL ; 
 void* TRANS_RESULT_OK ; 
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int rtsx_pre_handle_interrupt (struct rtsx_chip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rtsx_interrupt(int irq, void *dev_id)
{
	struct rtsx_dev *dev = dev_id;
	struct rtsx_chip *chip;
	int retval;
	u32 status;

	if (dev)
		chip = dev->chip;
	else
		return IRQ_NONE;

	if (!chip)
		return IRQ_NONE;

	spin_lock(&dev->reg_lock);

	retval = rtsx_pre_handle_interrupt(chip);
	if (retval == STATUS_FAIL) {
		spin_unlock(&dev->reg_lock);
		if (chip->int_reg == 0xFFFFFFFF)
			return IRQ_HANDLED;
		return IRQ_NONE;
	}

	status = chip->int_reg;

	if (dev->check_card_cd) {
		if (!(dev->check_card_cd & status)) {
			/* card not exist, return TRANS_RESULT_FAIL */
			dev->trans_result = TRANS_RESULT_FAIL;
			if (dev->done)
				complete(dev->done);
			goto exit;
		}
	}

	if (status & (NEED_COMPLETE_INT | DELINK_INT)) {
		if (status & (TRANS_FAIL_INT | DELINK_INT)) {
			if (status & DELINK_INT)
				RTSX_SET_DELINK(chip);
			dev->trans_result = TRANS_RESULT_FAIL;
			if (dev->done)
				complete(dev->done);
		} else if (status & TRANS_OK_INT) {
			dev->trans_result = TRANS_RESULT_OK;
			if (dev->done)
				complete(dev->done);
		} else if (status & DATA_DONE_INT) {
			dev->trans_result = TRANS_NOT_READY;
			if (dev->done && (dev->trans_state == STATE_TRANS_SG))
				complete(dev->done);
		}
	}

exit:
	spin_unlock(&dev->reg_lock);
	return IRQ_HANDLED;
}