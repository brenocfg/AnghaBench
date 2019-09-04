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
struct dma_device {int dummy; } ;
struct TYPE_2__ {struct dma_device dma_dev; } ;
struct sudmac_device {TYPE_1__ shdma_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 
 struct sudmac_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  shdma_cleanup (TYPE_1__*) ; 
 int /*<<< orphan*/  sudmac_chan_remove (struct sudmac_device*) ; 

__attribute__((used)) static int sudmac_remove(struct platform_device *pdev)
{
	struct sudmac_device *su_dev = platform_get_drvdata(pdev);
	struct dma_device *dma_dev = &su_dev->shdma_dev.dma_dev;

	dma_async_device_unregister(dma_dev);
	sudmac_chan_remove(su_dev);
	shdma_cleanup(&su_dev->shdma_dev);

	return 0;
}