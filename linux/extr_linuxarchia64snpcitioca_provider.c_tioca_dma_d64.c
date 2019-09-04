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
typedef  int u64 ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PHYS_TO_TIODMA (unsigned long) ; 

__attribute__((used)) static u64
tioca_dma_d64(unsigned long paddr)
{
	dma_addr_t bus_addr;

	bus_addr = PHYS_TO_TIODMA(paddr);

	BUG_ON(!bus_addr);
	BUG_ON(bus_addr >> 54);

	/* Set upper nibble to Cache Coherent Memory op */
	bus_addr |= (1UL << 60);

	return bus_addr;
}