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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ cpu_type; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 void* pcx_dma_alloc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ pcxl ; 
 scalar_t__ pcxl2 ; 
 void* pcxl_dma_alloc (struct device*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void *arch_dma_alloc(struct device *dev, size_t size,
		dma_addr_t *dma_handle, gfp_t gfp, unsigned long attrs)
{

	if (boot_cpu_data.cpu_type == pcxl2 || boot_cpu_data.cpu_type == pcxl)
		return pcxl_dma_alloc(dev, size, dma_handle, gfp, attrs);
	else
		return pcx_dma_alloc(dev, size, dma_handle, gfp, attrs);
}