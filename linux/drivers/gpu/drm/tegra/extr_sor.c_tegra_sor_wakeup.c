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
 int /*<<< orphan*/  SOR_TEST ; 
 unsigned long SOR_TEST_HEAD_MODE_AWAKE ; 
 unsigned long SOR_TEST_HEAD_MODE_MASK ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 unsigned long tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_sor_wakeup(struct tegra_sor *sor)
{
	unsigned long value, timeout;

	timeout = jiffies + msecs_to_jiffies(250);

	/* wait for head to wake up */
	while (time_before(jiffies, timeout)) {
		value = tegra_sor_readl(sor, SOR_TEST);
		value &= SOR_TEST_HEAD_MODE_MASK;

		if (value == SOR_TEST_HEAD_MODE_AWAKE)
			return 0;

		usleep_range(25, 100);
	}

	return -ETIMEDOUT;
}