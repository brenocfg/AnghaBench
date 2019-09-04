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
struct tpm_tis_data {int /*<<< orphan*/  locality; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_STS_COMMAND_READY ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_tis_write8 (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tpm_tis_ready(struct tpm_chip *chip)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	/* this causes the current command to be aborted */
	tpm_tis_write8(priv, TPM_STS(priv->locality), TPM_STS_COMMAND_READY);
}