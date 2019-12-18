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
typedef  int u8 ;
struct lm8333 {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LM8333_ERROR_FIFOOVR ; 
 int LM8333_ERROR_IRQ ; 
 int LM8333_ERROR_KEYOVR ; 
 int /*<<< orphan*/  LM8333_FIFO_READ ; 
 int LM8333_FIFO_TRANSFER_SIZE ; 
 int LM8333_KEYPAD_IRQ ; 
 int /*<<< orphan*/  LM8333_READ_ERROR ; 
 int /*<<< orphan*/  LM8333_READ_INT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lm8333_key_handler (struct lm8333*) ; 
 int lm8333_read8 (struct lm8333*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm8333_read_block (struct lm8333*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static irqreturn_t lm8333_irq_thread(int irq, void *data)
{
	struct lm8333 *lm8333 = data;
	u8 status = lm8333_read8(lm8333, LM8333_READ_INT);

	if (!status)
		return IRQ_NONE;

	if (status & LM8333_ERROR_IRQ) {
		u8 err = lm8333_read8(lm8333, LM8333_READ_ERROR);

		if (err & (LM8333_ERROR_KEYOVR | LM8333_ERROR_FIFOOVR)) {
			u8 dummy[LM8333_FIFO_TRANSFER_SIZE];

			lm8333_read_block(lm8333, LM8333_FIFO_READ,
					LM8333_FIFO_TRANSFER_SIZE, dummy);
		}
		dev_err(&lm8333->client->dev, "Got error %02x\n", err);
	}

	if (status & LM8333_KEYPAD_IRQ)
		lm8333_key_handler(lm8333);

	return IRQ_HANDLED;
}