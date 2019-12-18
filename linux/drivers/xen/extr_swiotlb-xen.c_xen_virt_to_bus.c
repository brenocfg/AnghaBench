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
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  virt_to_phys (void*) ; 
 int /*<<< orphan*/  xen_phys_to_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline dma_addr_t xen_virt_to_bus(void *address)
{
	return xen_phys_to_bus(virt_to_phys(address));
}