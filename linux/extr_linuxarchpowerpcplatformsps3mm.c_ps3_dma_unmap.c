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
struct ps3_dma_region {TYPE_1__* region_ops; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int (* unmap ) (struct ps3_dma_region*,int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (struct ps3_dma_region*,int /*<<< orphan*/ ,unsigned long) ; 

int ps3_dma_unmap(struct ps3_dma_region *r, dma_addr_t bus_addr,
	unsigned long len)
{
	return r->region_ops->unmap(r, bus_addr, len);
}