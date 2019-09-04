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
struct tpm_tis_data {int /*<<< orphan*/  locality; } ;
struct tpm_chip {int flags; unsigned long timeout_a; unsigned long timeout_d; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int /*<<< orphan*/  TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_TIMEOUT_USECS_MAX ; 
 int /*<<< orphan*/  TPM_TIMEOUT_USECS_MIN ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int tpm_tis_read32 (struct tpm_tis_data*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_burstcount(struct tpm_chip *chip)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	unsigned long stop;
	int burstcnt, rc;
	u32 value;

	/* wait for burstcount */
	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		stop = jiffies + chip->timeout_a;
	else
		stop = jiffies + chip->timeout_d;
	do {
		rc = tpm_tis_read32(priv, TPM_STS(priv->locality), &value);
		if (rc < 0)
			return rc;

		burstcnt = (value >> 8) & 0xFFFF;
		if (burstcnt)
			return burstcnt;
		usleep_range(TPM_TIMEOUT_USECS_MIN, TPM_TIMEOUT_USECS_MAX);
	} while (time_before(jiffies, stop));
	return -EBUSY;
}