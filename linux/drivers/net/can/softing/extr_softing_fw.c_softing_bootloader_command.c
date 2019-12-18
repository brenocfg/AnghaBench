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
struct softing {TYPE_1__* pdev; int /*<<< orphan*/ * dpram; } ;
typedef  int int16_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DPRAM_COMMAND ; 
 size_t DPRAM_RECEIPT ; 
 int ECANCELED ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int RES_NONE ; 
 int RES_OK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ *,char*,char const*,int) ; 
 int ioread16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

int softing_bootloader_command(struct softing *card, int16_t cmd,
		const char *msg)
{
	int ret;
	unsigned long stamp;

	iowrite16(RES_NONE, &card->dpram[DPRAM_RECEIPT]);
	iowrite16(cmd, &card->dpram[DPRAM_COMMAND]);
	/* be sure to flush this to the card */
	wmb();
	stamp = jiffies + 3 * HZ;
	/* wait for card */
	do {
		ret = ioread16(&card->dpram[DPRAM_RECEIPT]);
		/* don't have any cached variables */
		rmb();
		if (ret == RES_OK)
			return 0;
		if (time_after(jiffies, stamp))
			break;
		/* process context => relax */
		usleep_range(500, 10000);
	} while (!signal_pending(current));

	ret = (ret == RES_NONE) ? -ETIMEDOUT : -ECANCELED;
	dev_alert(&card->pdev->dev, "bootloader %s failed (%i)\n", msg, ret);
	return ret;
}