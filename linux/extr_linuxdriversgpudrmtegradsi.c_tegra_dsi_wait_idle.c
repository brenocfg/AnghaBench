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
struct tegra_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_STATUS ; 
 int DSI_STATUS_IDLE ; 
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int tegra_dsi_readl (struct tegra_dsi*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_dsi_wait_idle(struct tegra_dsi *dsi, unsigned long timeout)
{
	u32 value;

	timeout = jiffies + msecs_to_jiffies(timeout);

	while (time_before(jiffies, timeout)) {
		value = tegra_dsi_readl(dsi, DSI_STATUS);
		if (value & DSI_STATUS_IDLE)
			return 0;

		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}