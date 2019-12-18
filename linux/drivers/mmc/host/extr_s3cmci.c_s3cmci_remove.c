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
struct s3cmci_host {TYPE_2__* mem; int /*<<< orphan*/  base; int /*<<< orphan*/  irq; int /*<<< orphan*/  dma; int /*<<< orphan*/  pio_tasklet; int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mmc_host {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int S3C2410_GPE (int) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct s3cmci_host*) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (TYPE_2__*) ; 
 scalar_t__ s3cmci_host_usedma (struct s3cmci_host*) ; 
 int /*<<< orphan*/  s3cmci_shutdown (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3cmci_remove(struct platform_device *pdev)
{
	struct mmc_host		*mmc  = platform_get_drvdata(pdev);
	struct s3cmci_host	*host = mmc_priv(mmc);
	int i;

	s3cmci_shutdown(pdev);

	clk_put(host->clk);

	tasklet_disable(&host->pio_tasklet);

	if (s3cmci_host_usedma(host))
		dma_release_channel(host->dma);

	free_irq(host->irq, host);

	if (!pdev->dev.of_node)
		for (i = S3C2410_GPE(5); i <= S3C2410_GPE(10); i++)
			gpio_free(i);

	iounmap(host->base);
	release_mem_region(host->mem->start, resource_size(host->mem));

	mmc_free_host(mmc);
	return 0;
}