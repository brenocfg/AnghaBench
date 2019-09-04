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
struct dma_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_async_device_unregister (struct dma_device*) ; 

__attribute__((used)) static void dmam_device_release(struct device *dev, void *res)
{
	struct dma_device *device;

	device = *(struct dma_device **)res;
	dma_async_device_unregister(device);
}