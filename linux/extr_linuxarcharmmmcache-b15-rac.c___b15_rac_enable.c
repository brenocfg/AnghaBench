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
 scalar_t__ RAC_CONFIG0_REG ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ b15_rac_base ; 
 int /*<<< orphan*/  dsb () ; 

__attribute__((used)) static inline void __b15_rac_enable(u32 val)
{
	__raw_writel(val, b15_rac_base + RAC_CONFIG0_REG);
	/* dsb() is required here to be consistent with __flush_icache_all() */
	dsb();
}