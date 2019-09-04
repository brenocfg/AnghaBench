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
struct tegra_sor {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SOR_CRCA ; 
 int SOR_CRCA_VALID ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_sor_crc_wait(struct tegra_sor *sor, unsigned long timeout)
{
	u32 value;

	timeout = jiffies + msecs_to_jiffies(timeout);

	while (time_before(jiffies, timeout)) {
		value = tegra_sor_readl(sor, SOR_CRCA);
		if (value & SOR_CRCA_VALID)
			return 0;

		usleep_range(100, 200);
	}

	return -ETIMEDOUT;
}