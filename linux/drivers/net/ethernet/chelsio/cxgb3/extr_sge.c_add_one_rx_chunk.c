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
struct rx_desc {void* gen2; void* len_gen; void* addr_hi; void* addr_lo; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int V_FLD_GEN1 (unsigned int) ; 
 int V_FLD_GEN2 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 

__attribute__((used)) static inline int add_one_rx_chunk(dma_addr_t mapping, struct rx_desc *d,
				   unsigned int gen)
{
	d->addr_lo = cpu_to_be32(mapping);
	d->addr_hi = cpu_to_be32((u64) mapping >> 32);
	dma_wmb();
	d->len_gen = cpu_to_be32(V_FLD_GEN1(gen));
	d->gen2 = cpu_to_be32(V_FLD_GEN2(gen));
	return 0;
}