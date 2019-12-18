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
struct tegra_mipi {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MIPI_CAL_STATUS ; 
 int MIPI_CAL_STATUS_ACTIVE ; 
 int MIPI_CAL_STATUS_DONE ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int tegra_mipi_readl (struct tegra_mipi*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_mipi_wait(struct tegra_mipi *mipi)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(250);
	u32 value;

	while (time_before(jiffies, timeout)) {
		value = tegra_mipi_readl(mipi, MIPI_CAL_STATUS);
		if ((value & MIPI_CAL_STATUS_ACTIVE) == 0 &&
		    (value & MIPI_CAL_STATUS_DONE) != 0)
			return 0;

		usleep_range(10, 50);
	}

	return -ETIMEDOUT;
}