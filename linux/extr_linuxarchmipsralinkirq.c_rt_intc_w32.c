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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rt_intc_membase ; 
 scalar_t__* rt_intc_regs ; 

__attribute__((used)) static inline void rt_intc_w32(u32 val, unsigned reg)
{
	__raw_writel(val, rt_intc_membase + rt_intc_regs[reg]);
}