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
typedef  int /*<<< orphan*/  u8 ;
struct lm3533_als {int /*<<< orphan*/  irq; TYPE_1__* pdev; int /*<<< orphan*/  lm3533; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_LOW ; 
 int /*<<< orphan*/  LM3533_ALS_INT_ENABLE_MASK ; 
 int /*<<< orphan*/  LM3533_REG_ALS_ZONE_INFO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lm3533_als_isr ; 
 int lm3533_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int lm3533_als_setup_irq(struct lm3533_als *als, void *dev)
{
	u8 mask = LM3533_ALS_INT_ENABLE_MASK;
	int ret;

	/* Make sure interrupts are disabled. */
	ret = lm3533_update(als->lm3533, LM3533_REG_ALS_ZONE_INFO, 0, mask);
	if (ret) {
		dev_err(&als->pdev->dev, "failed to disable interrupts\n");
		return ret;
	}

	ret = request_threaded_irq(als->irq, NULL, lm3533_als_isr,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					dev_name(&als->pdev->dev), dev);
	if (ret) {
		dev_err(&als->pdev->dev, "failed to request irq %d\n",
								als->irq);
		return ret;
	}

	return 0;
}