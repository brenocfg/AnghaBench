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
struct tpm_chip {unsigned long timeout_d; int /*<<< orphan*/  dev; } ;
struct st33zp24_dev {int /*<<< orphan*/  phy_id; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* recv ) (int /*<<< orphan*/ ,scalar_t__,int*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ TPM_STS ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 struct st33zp24_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__,int*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int get_burstcount(struct tpm_chip *chip)
{
	struct st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	unsigned long stop;
	int burstcnt, status;
	u8 temp;

	stop = jiffies + chip->timeout_d;
	do {
		status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_STS + 1,
					    &temp, 1);
		if (status < 0)
			return -EBUSY;

		burstcnt = temp;
		status = tpm_dev->ops->recv(tpm_dev->phy_id, TPM_STS + 2,
					    &temp, 1);
		if (status < 0)
			return -EBUSY;

		burstcnt |= temp << 8;
		if (burstcnt)
			return burstcnt;
		msleep(TPM_TIMEOUT);
	} while (time_before(jiffies, stop));
	return -EBUSY;
}