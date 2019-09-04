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
typedef  int u8 ;
struct ican3_dev {int num; int /*<<< orphan*/  ndev; scalar_t__ dpm; TYPE_2__* dpmctrl; int /*<<< orphan*/  free_page; TYPE_1__* ctrl; } ;
struct TYPE_4__ {int /*<<< orphan*/  hwreset; } ;
struct TYPE_3__ {int /*<<< orphan*/  int_disable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FREE_START ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  QUEUE_OLD_CONTROL ; 
 scalar_t__ TARGET_RUNNING ; 
 int /*<<< orphan*/  ican3_set_page (struct ican3_dev*,int /*<<< orphan*/ ) ; 
 int ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ican3_reset_module(struct ican3_dev *mod)
{
	unsigned long start;
	u8 runold, runnew;

	/* disable interrupts so no more work is scheduled */
	iowrite8(1 << mod->num, &mod->ctrl->int_disable);

	/* the first unallocated page in the DPM is #9 */
	mod->free_page = DPM_FREE_START;

	ican3_set_page(mod, QUEUE_OLD_CONTROL);
	runold = ioread8(mod->dpm + TARGET_RUNNING);

	/* reset the module */
	iowrite8(0x00, &mod->dpmctrl->hwreset);

	/* wait until the module has finished resetting and is running */
	start = jiffies;
	do {
		ican3_set_page(mod, QUEUE_OLD_CONTROL);
		runnew = ioread8(mod->dpm + TARGET_RUNNING);
		if (runnew == (runold ^ 0xff))
			return 0;

		msleep(10);
	} while (time_before(jiffies, start + HZ / 2));

	netdev_err(mod->ndev, "failed to reset CAN module\n");
	return -ETIMEDOUT;
}