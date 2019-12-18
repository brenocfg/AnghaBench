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
struct ccw_device {int /*<<< orphan*/  dev; TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_pool; } ;

/* Variables and functions */
 void* cio_gp_dma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

void *ccw_device_dma_zalloc(struct ccw_device *cdev, size_t size)
{
	return cio_gp_dma_zalloc(cdev->private->dma_pool, &cdev->dev, size);
}