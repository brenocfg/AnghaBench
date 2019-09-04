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
struct platform_device {int dummy; } ;
struct device {int dummy; } ;
struct bcm2835_smi_instance {int /*<<< orphan*/  clk; int /*<<< orphan*/  dma_chan; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_all (int /*<<< orphan*/ ) ; 
 struct bcm2835_smi_instance* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int bcm2835_smi_remove(struct platform_device *pdev)
{
	struct bcm2835_smi_instance *inst = platform_get_drvdata(pdev);
	struct device *dev = inst->dev;

	dmaengine_terminate_all(inst->dma_chan);
	dma_release_channel(inst->dma_chan);

	clk_disable_unprepare(inst->clk);

	dev_info(dev, "SMI device removed - OK");
	return 0;
}