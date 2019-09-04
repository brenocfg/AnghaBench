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
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 void* KERNBASE ; 
 int kern_base ; 

__attribute__((used)) static inline resource_size_t compute_kern_paddr(void *addr)
{
	return (resource_size_t) (addr - KERNBASE + kern_base);
}