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
typedef  int u32 ;

/* Variables and functions */
 int FLUSH_RAC ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ b15_rac_base ; 
 int /*<<< orphan*/  dmb () ; 
 scalar_t__ rac_flush_offset ; 

__attribute__((used)) static inline void __b15_rac_flush(void)
{
	u32 reg;

	__raw_writel(FLUSH_RAC, b15_rac_base + rac_flush_offset);
	do {
		/* This dmb() is required to force the Bus Interface Unit
		 * to clean oustanding writes, and forces an idle cycle
		 * to be inserted.
		 */
		dmb();
		reg = __raw_readl(b15_rac_base + rac_flush_offset);
	} while (reg & FLUSH_RAC);
}