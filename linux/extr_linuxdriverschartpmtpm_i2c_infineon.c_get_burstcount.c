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
struct tpm_chip {unsigned long timeout_d; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  locality; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ TPM_STS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_HI ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_LOW ; 
 scalar_t__ iic_tpm_read (scalar_t__,int*,int) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 TYPE_1__ tpm_dev ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t get_burstcount(struct tpm_chip *chip)
{
	unsigned long stop;
	ssize_t burstcnt;
	u8 buf[3];

	/* wait for burstcount */
	/* which timeout value, spec has 2 answers (c & d) */
	stop = jiffies + chip->timeout_d;
	do {
		/* Note: STS is little endian */
		if (iic_tpm_read(TPM_STS(tpm_dev.locality)+1, buf, 3) < 0)
			burstcnt = 0;
		else
			burstcnt = (buf[2] << 16) + (buf[1] << 8) + buf[0];

		if (burstcnt)
			return burstcnt;

		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
	} while (time_before(jiffies, stop));
	return -EBUSY;
}