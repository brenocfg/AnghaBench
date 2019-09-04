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
struct dma_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ ,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (void*) ; 
 int dma_async_device_register (struct dma_device*) ; 
 int /*<<< orphan*/  dmam_device_release ; 

int dmaenginem_async_device_register(struct dma_device *device)
{
	void *p;
	int ret;

	p = devres_alloc(dmam_device_release, sizeof(void *), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	ret = dma_async_device_register(device);
	if (!ret) {
		*(struct dma_device **)p = device;
		devres_add(device->dev, p);
	} else {
		devres_free(p);
	}

	return ret;
}