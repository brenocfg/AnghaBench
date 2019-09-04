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
struct tegra_dsi {scalar_t__ regs; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  trace_dsi_writel (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void tegra_dsi_writel(struct tegra_dsi *dsi, u32 value,
				    unsigned int offset)
{
	trace_dsi_writel(dsi->dev, offset, value);
	writel(value, dsi->regs + (offset << 2));
}