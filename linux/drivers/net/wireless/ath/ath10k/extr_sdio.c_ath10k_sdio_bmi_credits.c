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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ATH10K_HIF_MBOX_NUM_MAX ; 
 unsigned long BMI_COMMUNICATION_TIMEOUT_HZ ; 
 int ETIMEDOUT ; 
 int MBOX_COUNT_DEC_ADDRESS ; 
 int ath10k_sdio_read32 (struct ath10k*,int,int*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ath10k_sdio_bmi_credits(struct ath10k *ar)
{
	u32 addr, cmd_credits;
	unsigned long timeout;
	int ret;

	/* Read the counter register to get the command credits */
	addr = MBOX_COUNT_DEC_ADDRESS + ATH10K_HIF_MBOX_NUM_MAX * 4;
	timeout = jiffies + BMI_COMMUNICATION_TIMEOUT_HZ;
	cmd_credits = 0;

	while (time_before(jiffies, timeout) && !cmd_credits) {
		/* Hit the credit counter with a 4-byte access, the first byte
		 * read will hit the counter and cause a decrement, while the
		 * remaining 3 bytes has no effect. The rationale behind this
		 * is to make all HIF accesses 4-byte aligned.
		 */
		ret = ath10k_sdio_read32(ar, addr, &cmd_credits);
		if (ret) {
			ath10k_warn(ar,
				    "unable to decrement the command credit count register: %d\n",
				    ret);
			return ret;
		}

		/* The counter is only 8 bits.
		 * Ignore anything in the upper 3 bytes
		 */
		cmd_credits &= 0xFF;
	}

	if (!cmd_credits) {
		ath10k_warn(ar, "bmi communication timeout\n");
		return -ETIMEDOUT;
	}

	return 0;
}