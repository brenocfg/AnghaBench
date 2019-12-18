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
struct sh_flctl {int qos_request; TYPE_1__* pdev; int /*<<< orphan*/  holden; int /*<<< orphan*/  pm_qos; int /*<<< orphan*/  flcmncr_base; } ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CE0_ENABLE ; 
 int /*<<< orphan*/  DEV_PM_QOS_RESUME_LATENCY ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  FLHOLDCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  HOLDEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int dev_pm_qos_add_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_pm_qos_remove_request (int /*<<< orphan*/ *) ; 
 struct sh_flctl* mtd_to_flctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flctl_select_chip(struct nand_chip *chip, int chipnr)
{
	struct sh_flctl *flctl = mtd_to_flctl(nand_to_mtd(chip));
	int ret;

	switch (chipnr) {
	case -1:
		flctl->flcmncr_base &= ~CE0_ENABLE;

		pm_runtime_get_sync(&flctl->pdev->dev);
		writel(flctl->flcmncr_base, FLCMNCR(flctl));

		if (flctl->qos_request) {
			dev_pm_qos_remove_request(&flctl->pm_qos);
			flctl->qos_request = 0;
		}

		pm_runtime_put_sync(&flctl->pdev->dev);
		break;
	case 0:
		flctl->flcmncr_base |= CE0_ENABLE;

		if (!flctl->qos_request) {
			ret = dev_pm_qos_add_request(&flctl->pdev->dev,
							&flctl->pm_qos,
							DEV_PM_QOS_RESUME_LATENCY,
							100);
			if (ret < 0)
				dev_err(&flctl->pdev->dev,
					"PM QoS request failed: %d\n", ret);
			flctl->qos_request = 1;
		}

		if (flctl->holden) {
			pm_runtime_get_sync(&flctl->pdev->dev);
			writel(HOLDEN, FLHOLDCR(flctl));
			pm_runtime_put_sync(&flctl->pdev->dev);
		}
		break;
	default:
		BUG();
	}
}