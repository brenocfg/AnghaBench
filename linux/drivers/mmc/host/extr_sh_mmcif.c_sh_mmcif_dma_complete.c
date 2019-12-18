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
struct sh_mmcif_host {int /*<<< orphan*/  dma_complete; struct mmc_request* mrq; } ;
struct mmc_request {int /*<<< orphan*/  data; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* sh_mmcif_host_to_dev (struct sh_mmcif_host*) ; 

__attribute__((used)) static void sh_mmcif_dma_complete(void *arg)
{
	struct sh_mmcif_host *host = arg;
	struct mmc_request *mrq = host->mrq;
	struct device *dev = sh_mmcif_host_to_dev(host);

	dev_dbg(dev, "Command completed\n");

	if (WARN(!mrq || !mrq->data, "%s: NULL data in DMA completion!\n",
		 dev_name(dev)))
		return;

	complete(&host->dma_complete);
}