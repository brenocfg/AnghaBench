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
struct _diva_dma_map_entry {void* addr_handle; void* local_ram_addr; int /*<<< orphan*/  phys_bus_addr; } ;
typedef  int /*<<< orphan*/  dword ;

/* Variables and functions */

void diva_init_dma_map_entry(struct _diva_dma_map_entry *pmap,
			     int nr, void *virt, dword phys,
			     void *addr_handle) {
	pmap[nr].phys_bus_addr  = phys;
	pmap[nr].local_ram_addr = virt;
	pmap[nr].addr_handle    = addr_handle;
}