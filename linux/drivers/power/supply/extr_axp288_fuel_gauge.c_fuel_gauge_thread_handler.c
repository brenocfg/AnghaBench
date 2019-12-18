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
struct axp288_fg_info {int* irq; int /*<<< orphan*/  bat; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AXP288_FG_INTR_NUM ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
#define  QWBTO_IRQ 133 
#define  QWBTU_IRQ 132 
#define  WBTO_IRQ 131 
#define  WBTU_IRQ 130 
#define  WL1_IRQ 129 
#define  WL2_IRQ 128 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t fuel_gauge_thread_handler(int irq, void *dev)
{
	struct axp288_fg_info *info = dev;
	int i;

	for (i = 0; i < AXP288_FG_INTR_NUM; i++) {
		if (info->irq[i] == irq)
			break;
	}

	if (i >= AXP288_FG_INTR_NUM) {
		dev_warn(&info->pdev->dev, "spurious interrupt!!\n");
		return IRQ_NONE;
	}

	switch (i) {
	case QWBTU_IRQ:
		dev_info(&info->pdev->dev,
			"Quit Battery under temperature in work mode IRQ (QWBTU)\n");
		break;
	case WBTU_IRQ:
		dev_info(&info->pdev->dev,
			"Battery under temperature in work mode IRQ (WBTU)\n");
		break;
	case QWBTO_IRQ:
		dev_info(&info->pdev->dev,
			"Quit Battery over temperature in work mode IRQ (QWBTO)\n");
		break;
	case WBTO_IRQ:
		dev_info(&info->pdev->dev,
			"Battery over temperature in work mode IRQ (WBTO)\n");
		break;
	case WL2_IRQ:
		dev_info(&info->pdev->dev, "Low Batt Warning(2) INTR\n");
		break;
	case WL1_IRQ:
		dev_info(&info->pdev->dev, "Low Batt Warning(1) INTR\n");
		break;
	default:
		dev_warn(&info->pdev->dev, "Spurious Interrupt!!!\n");
	}

	power_supply_changed(info->bat);
	return IRQ_HANDLED;
}