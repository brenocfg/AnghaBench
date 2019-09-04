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
struct TYPE_4__ {int /*<<< orphan*/  dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; } ;
struct qup_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  adap; int /*<<< orphan*/  irq; TYPE_2__ brx; TYPE_1__ btx; scalar_t__ is_dma; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 struct qup_i2c_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qup_i2c_disable_clocks (struct qup_i2c_dev*) ; 

__attribute__((used)) static int qup_i2c_remove(struct platform_device *pdev)
{
	struct qup_i2c_dev *qup = platform_get_drvdata(pdev);

	if (qup->is_dma) {
		dma_release_channel(qup->btx.dma);
		dma_release_channel(qup->brx.dma);
	}

	disable_irq(qup->irq);
	qup_i2c_disable_clocks(qup);
	i2c_del_adapter(&qup->adap);
	pm_runtime_disable(qup->dev);
	pm_runtime_set_suspended(qup->dev);
	return 0;
}