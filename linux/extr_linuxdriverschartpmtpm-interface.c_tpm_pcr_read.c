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
typedef  int /*<<< orphan*/  u8 ;
struct tpm_chip {int flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm2_pcr_read (struct tpm_chip*,int,int /*<<< orphan*/ *) ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int tpm_pcr_read_dev (struct tpm_chip*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 

int tpm_pcr_read(struct tpm_chip *chip, int pcr_idx, u8 *res_buf)
{
	int rc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		return -ENODEV;
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_pcr_read(chip, pcr_idx, res_buf);
	else
		rc = tpm_pcr_read_dev(chip, pcr_idx, res_buf);
	tpm_put_ops(chip);
	return rc;
}