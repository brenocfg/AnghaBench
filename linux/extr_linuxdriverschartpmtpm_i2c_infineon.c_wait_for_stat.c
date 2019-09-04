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
typedef  int u8 ;
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_HI ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_LOW ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int tpm_tis_i2c_status (struct tpm_chip*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_for_stat(struct tpm_chip *chip, u8 mask, unsigned long timeout,
			 int *status)
{
	unsigned long stop;

	/* check current status */
	*status = tpm_tis_i2c_status(chip);
	if ((*status != 0xFF) && (*status & mask) == mask)
		return 0;

	stop = jiffies + timeout;
	do {
		/* since we just checked the status, give the TPM some time */
		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
		*status = tpm_tis_i2c_status(chip);
		if ((*status & mask) == mask)
			return 0;

	} while (time_before(jiffies, stop));

	return -ETIME;
}