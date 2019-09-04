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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct st33zp24_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  intrs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct st33zp24_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tpm_ioserirq_handler(int irq, void *dev_id)
{
	struct tpm_chip *chip = dev_id;
	struct st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);

	tpm_dev->intrs++;
	wake_up_interruptible(&tpm_dev->read_queue);
	disable_irq_nosync(tpm_dev->irq);

	return IRQ_HANDLED;
}