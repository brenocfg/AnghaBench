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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap2_onenand {scalar_t__ dma_chan; int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 struct omap2_onenand* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  omap2_onenand_shutdown (struct platform_device*) ; 
 int /*<<< orphan*/  onenand_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap2_onenand_remove(struct platform_device *pdev)
{
	struct omap2_onenand *c = dev_get_drvdata(&pdev->dev);

	onenand_release(&c->mtd);
	if (c->dma_chan)
		dma_release_channel(c->dma_chan);
	omap2_onenand_shutdown(pdev);

	return 0;
}