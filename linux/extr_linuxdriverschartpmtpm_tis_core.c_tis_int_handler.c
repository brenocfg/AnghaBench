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
struct tpm_tis_data {int irq_tested; int /*<<< orphan*/  locality; int /*<<< orphan*/  int_queue; int /*<<< orphan*/  read_queue; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int TPM_INTF_CMD_READY_INT ; 
 int TPM_INTF_DATA_AVAIL_INT ; 
 int TPM_INTF_LOCALITY_CHANGE_INT ; 
 int TPM_INTF_STS_VALID_INT ; 
 int /*<<< orphan*/  TPM_INT_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ check_locality (struct tpm_chip*,int) ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int*) ; 
 int tpm_tis_write32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t tis_int_handler(int dummy, void *dev_id)
{
	struct tpm_chip *chip = dev_id;
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	u32 interrupt;
	int i, rc;

	rc = tpm_tis_read32(priv, TPM_INT_STATUS(priv->locality), &interrupt);
	if (rc < 0)
		return IRQ_NONE;

	if (interrupt == 0)
		return IRQ_NONE;

	priv->irq_tested = true;
	if (interrupt & TPM_INTF_DATA_AVAIL_INT)
		wake_up_interruptible(&priv->read_queue);
	if (interrupt & TPM_INTF_LOCALITY_CHANGE_INT)
		for (i = 0; i < 5; i++)
			if (check_locality(chip, i))
				break;
	if (interrupt &
	    (TPM_INTF_LOCALITY_CHANGE_INT | TPM_INTF_STS_VALID_INT |
	     TPM_INTF_CMD_READY_INT))
		wake_up_interruptible(&priv->int_queue);

	/* Clear interrupts handled with TPM_EOI */
	rc = tpm_tis_write32(priv, TPM_INT_STATUS(priv->locality), interrupt);
	if (rc < 0)
		return IRQ_NONE;

	tpm_tis_read32(priv, TPM_INT_STATUS(priv->locality), &interrupt);
	return IRQ_HANDLED;
}