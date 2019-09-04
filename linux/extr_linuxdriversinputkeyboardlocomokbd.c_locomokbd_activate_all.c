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
 scalar_t__ LOCOMO_KIC ; 
 scalar_t__ LOCOMO_KSC ; 
 unsigned long locomo_readl (scalar_t__) ; 
 int /*<<< orphan*/  locomo_writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline void locomokbd_activate_all(unsigned long membase)
{
	unsigned long r;

	locomo_writel(0, membase + LOCOMO_KSC);
	r = locomo_readl(membase + LOCOMO_KIC);
	r &= 0xFEFF;
	locomo_writel(r, membase + LOCOMO_KIC);
}