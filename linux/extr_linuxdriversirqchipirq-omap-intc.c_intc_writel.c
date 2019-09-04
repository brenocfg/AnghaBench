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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ omap_irq_base ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void intc_writel(u32 reg, u32 val)
{
	writel_relaxed(val, omap_irq_base + reg);
}