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
struct TYPE_2__ {void* addr_hi; void* addr_lo; } ;
union bfi_addr_u {TYPE_1__ a32; } ;
typedef  int u64 ;

/* Variables and functions */
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static inline void
__bfa_dma_be_addr_set(union bfi_addr_u *dma_addr, u64 pa)
{
	dma_addr->a32.addr_lo = cpu_to_be32(pa);
	dma_addr->a32.addr_hi = cpu_to_be32(pa >> 32);
}