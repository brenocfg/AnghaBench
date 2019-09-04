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
typedef  int /*<<< orphan*/  u8 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct crb_priv {size_t cmd_size; scalar_t__ sm; int /*<<< orphan*/  smc_func_id; TYPE_1__* regs_t; int /*<<< orphan*/  hid; int /*<<< orphan*/  cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_start; int /*<<< orphan*/  ctrl_cancel; } ;

/* Variables and functions */
 scalar_t__ ACPI_TPM2_COMMAND_BUFFER ; 
 scalar_t__ ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC ; 
 scalar_t__ ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD ; 
 scalar_t__ ACPI_TPM2_MEMORY_MAPPED ; 
 scalar_t__ ACPI_TPM2_START_METHOD ; 
 int /*<<< orphan*/  CRB_START_INVOKE ; 
 int E2BIG ; 
 int crb_do_acpi_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 struct crb_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int tpm_crb_smc_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int crb_send(struct tpm_chip *chip, u8 *buf, size_t len)
{
	struct crb_priv *priv = dev_get_drvdata(&chip->dev);
	int rc = 0;

	/* Zero the cancel register so that the next command will not get
	 * canceled.
	 */
	iowrite32(0, &priv->regs_t->ctrl_cancel);

	if (len > priv->cmd_size) {
		dev_err(&chip->dev, "invalid command count value %zd %d\n",
			len, priv->cmd_size);
		return -E2BIG;
	}

	memcpy_toio(priv->cmd, buf, len);

	/* Make sure that cmd is populated before issuing start. */
	wmb();

	/* The reason for the extra quirk is that the PTT in 4th Gen Core CPUs
	 * report only ACPI start but in practice seems to require both
	 * CRB start, hence invoking CRB start method if hid == MSFT0101.
	 */
	if ((priv->sm == ACPI_TPM2_COMMAND_BUFFER) ||
	    (priv->sm == ACPI_TPM2_MEMORY_MAPPED) ||
	    (!strcmp(priv->hid, "MSFT0101")))
		iowrite32(CRB_START_INVOKE, &priv->regs_t->ctrl_start);

	if ((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD))
		rc = crb_do_acpi_start(chip);

	if (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC) {
		iowrite32(CRB_START_INVOKE, &priv->regs_t->ctrl_start);
		rc = tpm_crb_smc_start(&chip->dev, priv->smc_func_id);
	}

	return rc;
}