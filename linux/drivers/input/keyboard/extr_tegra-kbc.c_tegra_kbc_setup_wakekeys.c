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
struct tegra_kbc {scalar_t__ mmio; TYPE_1__* hw_support; int /*<<< orphan*/  wakeup; } ;
struct TYPE_2__ {int max_rows; } ;

/* Variables and functions */
 scalar_t__ KBC_ROW0_MASK_0 ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void tegra_kbc_setup_wakekeys(struct tegra_kbc *kbc, bool filter)
{
	int i;
	unsigned int rst_val;

	/* Either mask all keys or none. */
	rst_val = (filter && !kbc->wakeup) ? ~0 : 0;

	for (i = 0; i < kbc->hw_support->max_rows; i++)
		writel(rst_val, kbc->mmio + KBC_ROW0_MASK_0 + i * 4);
}