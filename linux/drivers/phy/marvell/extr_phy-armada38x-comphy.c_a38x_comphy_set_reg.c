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
struct a38x_comphy_lane {scalar_t__ base; } ;

/* Variables and functions */
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void a38x_comphy_set_reg(struct a38x_comphy_lane *lane,
				unsigned int offset, u32 mask, u32 value)
{
	u32 val;

	val = readl_relaxed(lane->base + offset) & ~mask;
	writel(val | value, lane->base + offset);
}