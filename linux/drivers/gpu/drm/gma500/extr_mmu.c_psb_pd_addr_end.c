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

/* Variables and functions */
 unsigned long PSB_PDE_MASK ; 

__attribute__((used)) static inline unsigned long psb_pd_addr_end(unsigned long addr,
					    unsigned long end)
{
	addr = (addr + PSB_PDE_MASK + 1) & ~PSB_PDE_MASK;
	return (addr < end) ? addr : end;
}