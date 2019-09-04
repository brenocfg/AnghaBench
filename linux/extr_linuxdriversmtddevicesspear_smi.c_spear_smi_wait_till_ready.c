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
typedef  int /*<<< orphan*/  u32 ;
struct spear_smi {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIMEDOUT ; 
 int SR_WIP ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int spear_smi_read_sr (struct spear_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static int spear_smi_wait_till_ready(struct spear_smi *dev, u32 bank,
		unsigned long timeout)
{
	unsigned long finish;
	int status;

	finish = jiffies + timeout;
	do {
		status = spear_smi_read_sr(dev, bank);
		if (status < 0) {
			if (status == -ETIMEDOUT)
				continue; /* try till finish */
			return status;
		} else if (!(status & SR_WIP)) {
			return 0;
		}

		cond_resched();
	} while (!time_after_eq(jiffies, finish));

	dev_err(&dev->pdev->dev, "smi controller is busy, timeout\n");
	return -EBUSY;
}