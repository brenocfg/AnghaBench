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
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  cio_gp_dma_free (int /*<<< orphan*/ ,void*,size_t) ; 

void ccw_device_dma_free(struct ccw_device *cdev, void *cpu_addr, size_t size)
{
	cio_gp_dma_free(cdev->private->dma_pool, cpu_addr, size);
}