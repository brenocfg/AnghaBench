#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct aac_dev {TYPE_1__* IndexRegs; scalar_t__ msi_enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  ODR_C; } ;
struct TYPE_3__ {int /*<<< orphan*/ * Mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_CLEAR_SYNC_BIT ; 
 int HZ ; 
 TYPE_2__ MUnit ; 
 int OUTBOUNDDOORBELL_0 ; 
 int SRC_ODR_SHIFT ; 
 int USEC_PER_MSEC ; 
 int /*<<< orphan*/  aac_src_access_devreg (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int aac_src_get_sync_status (struct aac_dev*) ; 
 unsigned long jiffies ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,unsigned long) ; 

__attribute__((used)) static int aac_src_wait_sync(struct aac_dev *dev, int *status)
{
	unsigned long start = jiffies;
	unsigned long usecs = 0;
	int delay = 5 * HZ;
	int rc = 1;

	while (time_before(jiffies, start+delay)) {
		/*
		 * Delay 5 microseconds to let Mon960 get info.
		 */
		udelay(5);

		/*
		 * Mon960 will set doorbell0 bit when it has completed the
		 * command.
		 */
		if (aac_src_get_sync_status(dev) & OUTBOUNDDOORBELL_0) {
			/*
			 * Clear: the doorbell.
			 */
			if (dev->msi_enabled)
				aac_src_access_devreg(dev, AAC_CLEAR_SYNC_BIT);
			else
				src_writel(dev, MUnit.ODR_C,
					OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
			rc = 0;

			break;
		}

		/*
		 * Yield the processor in case we are slow
		 */
		usecs = 1 * USEC_PER_MSEC;
		usleep_range(usecs, usecs + 50);
	}
	/*
	 * Pull the synch status from Mailbox 0.
	 */
	if (status && !rc) {
		status[0] = readl(&dev->IndexRegs->Mailbox[0]);
		status[1] = readl(&dev->IndexRegs->Mailbox[1]);
		status[2] = readl(&dev->IndexRegs->Mailbox[2]);
		status[3] = readl(&dev->IndexRegs->Mailbox[3]);
		status[4] = readl(&dev->IndexRegs->Mailbox[4]);
	}

	return rc;
}