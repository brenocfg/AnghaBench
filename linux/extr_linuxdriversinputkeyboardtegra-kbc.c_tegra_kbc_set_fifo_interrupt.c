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
struct tegra_kbc {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ KBC_CONTROL_0 ; 
 int /*<<< orphan*/  KBC_CONTROL_FIFO_CNT_INT_EN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_kbc_set_fifo_interrupt(struct tegra_kbc *kbc, bool enable)
{
	u32 val;

	val = readl(kbc->mmio + KBC_CONTROL_0);
	if (enable)
		val |= KBC_CONTROL_FIFO_CNT_INT_EN;
	else
		val &= ~KBC_CONTROL_FIFO_CNT_INT_EN;
	writel(val, kbc->mmio + KBC_CONTROL_0);
}