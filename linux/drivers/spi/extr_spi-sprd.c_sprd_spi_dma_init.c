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
struct TYPE_2__ {int enable; } ;
struct sprd_spi {TYPE_1__ dma; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int sprd_spi_dma_request (struct sprd_spi*) ; 

__attribute__((used)) static int sprd_spi_dma_init(struct platform_device *pdev, struct sprd_spi *ss)
{
	int ret;

	ret = sprd_spi_dma_request(ss);
	if (ret) {
		if (ret == -EPROBE_DEFER)
			return ret;

		dev_warn(&pdev->dev,
			 "failed to request dma, enter no dma mode, ret = %d\n",
			 ret);

		return 0;
	}

	ss->dma.enable = true;

	return 0;
}