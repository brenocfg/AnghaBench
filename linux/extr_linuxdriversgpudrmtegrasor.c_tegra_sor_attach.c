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
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOR_SUPER_STATE1 ; 
 unsigned long SOR_SUPER_STATE_ATTACHED ; 
 unsigned long SOR_SUPER_STATE_HEAD_MODE_AWAKE ; 
 unsigned long SOR_SUPER_STATE_MODE_NORMAL ; 
 int /*<<< orphan*/  SOR_TEST ; 
 unsigned long SOR_TEST_ATTACHED ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned long tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_super_update (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_sor_attach(struct tegra_sor *sor)
{
	unsigned long value, timeout;

	/* wake up in normal mode */
	value = tegra_sor_readl(sor, SOR_SUPER_STATE1);
	value |= SOR_SUPER_STATE_HEAD_MODE_AWAKE;
	value |= SOR_SUPER_STATE_MODE_NORMAL;
	tegra_sor_writel(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	/* attach */
	value = tegra_sor_readl(sor, SOR_SUPER_STATE1);
	value |= SOR_SUPER_STATE_ATTACHED;
	tegra_sor_writel(sor, value, SOR_SUPER_STATE1);
	tegra_sor_super_update(sor);

	timeout = jiffies + msecs_to_jiffies(250);

	while (time_before(jiffies, timeout)) {
		value = tegra_sor_readl(sor, SOR_TEST);
		if ((value & SOR_TEST_ATTACHED) != 0)
			return 0;

		usleep_range(25, 100);
	}

	return -ETIMEDOUT;
}