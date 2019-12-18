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
struct resource {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  coherent_dma_mask; int /*<<< orphan*/ * dma_mask; struct TYPE_2__* parent; } ;
struct platform_device {unsigned int num_resources; TYPE_1__ dev; struct resource* resource; } ;
struct fsl_usb2_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  dma_set_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct fsl_usb2_platform_data*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource const*,unsigned int) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static struct platform_device *fsl_usb2_device_register(
					struct platform_device *ofdev,
					struct fsl_usb2_platform_data *pdata,
					const char *name, int id)
{
	struct platform_device *pdev;
	const struct resource *res = ofdev->resource;
	unsigned int num = ofdev->num_resources;
	int retval;

	pdev = platform_device_alloc(name, id);
	if (!pdev) {
		retval = -ENOMEM;
		goto error;
	}

	pdev->dev.parent = &ofdev->dev;

	pdev->dev.coherent_dma_mask = ofdev->dev.coherent_dma_mask;

	if (!pdev->dev.dma_mask)
		pdev->dev.dma_mask = &ofdev->dev.coherent_dma_mask;
	else
		dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));

	retval = platform_device_add_data(pdev, pdata, sizeof(*pdata));
	if (retval)
		goto error;

	if (num) {
		retval = platform_device_add_resources(pdev, res, num);
		if (retval)
			goto error;
	}

	retval = platform_device_add(pdev);
	if (retval)
		goto error;

	return pdev;

error:
	platform_device_put(pdev);
	return ERR_PTR(retval);
}