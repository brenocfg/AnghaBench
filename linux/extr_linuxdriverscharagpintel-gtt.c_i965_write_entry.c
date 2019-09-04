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
typedef  int u32 ;
typedef  int dma_addr_t ;
struct TYPE_2__ {scalar_t__ gtt; } ;

/* Variables and functions */
 unsigned int AGP_USER_CACHED_MEMORY ; 
 int I810_PTE_VALID ; 
 int I830_PTE_SYSTEM_CACHED ; 
 TYPE_1__ intel_private ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void i965_write_entry(dma_addr_t addr,
			     unsigned int entry,
			     unsigned int flags)
{
	u32 pte_flags;

	pte_flags = I810_PTE_VALID;
	if (flags == AGP_USER_CACHED_MEMORY)
		pte_flags |= I830_PTE_SYSTEM_CACHED;

	/* Shift high bits down */
	addr |= (addr >> 28) & 0xf0;
	writel_relaxed(addr | pte_flags, intel_private.gtt + entry);
}