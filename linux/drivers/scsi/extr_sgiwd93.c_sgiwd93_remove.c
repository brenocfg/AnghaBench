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
struct sgiwd93_platform_data {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {struct sgiwd93_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ip22_hostdata {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpu; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NON_CONSISTENT ; 
 int /*<<< orphan*/  HPC_DMA_SIZE ; 
 int /*<<< orphan*/  dma_free_attrs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct Scsi_Host*) ; 
 struct Scsi_Host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 

__attribute__((used)) static int sgiwd93_remove(struct platform_device *pdev)
{
	struct Scsi_Host *host = platform_get_drvdata(pdev);
	struct ip22_hostdata *hdata = (struct ip22_hostdata *) host->hostdata;
	struct sgiwd93_platform_data *pd = pdev->dev.platform_data;

	scsi_remove_host(host);
	free_irq(pd->irq, host);
	dma_free_attrs(&pdev->dev, HPC_DMA_SIZE, hdata->cpu, hdata->dma,
		       DMA_ATTR_NON_CONSISTENT);
	scsi_host_put(host);
	return 0;
}