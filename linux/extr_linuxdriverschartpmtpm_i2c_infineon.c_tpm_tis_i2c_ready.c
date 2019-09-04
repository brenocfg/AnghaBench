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
struct tpm_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  locality; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_STS_COMMAND_READY ; 
 int /*<<< orphan*/  iic_tpm_write_long (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static void tpm_tis_i2c_ready(struct tpm_chip *chip)
{
	/* this causes the current command to be aborted */
	u8 buf = TPM_STS_COMMAND_READY;
	iic_tpm_write_long(TPM_STS(tpm_dev.locality), &buf, 1);
}