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

/* Variables and functions */
 int TPM_CTRL_WTX ; 
 int /*<<< orphan*/  TPM_MAX_WTX_PACKAGES ; 
 int TPM_VL_VER ; 
 int /*<<< orphan*/  TPM_WTX_MSLEEP_TIME ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_wtx ; 
 int /*<<< orphan*/  tpm_msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_and_send (struct tpm_chip*,int) ; 

__attribute__((used)) static void tpm_wtx(struct tpm_chip *chip)
{
	number_of_wtx++;
	dev_info(&chip->dev, "Granting WTX (%02d / %02d)\n",
		 number_of_wtx, TPM_MAX_WTX_PACKAGES);
	wait_and_send(chip, TPM_VL_VER);
	wait_and_send(chip, TPM_CTRL_WTX);
	wait_and_send(chip, 0x00);
	wait_and_send(chip, 0x00);
	tpm_msleep(TPM_WTX_MSLEEP_TIME);
}