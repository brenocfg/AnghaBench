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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct tegra_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DSI_STATUS ; 
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int tegra_dsi_readl (struct tegra_dsi*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tegra_dsi_wait_for_response(struct tegra_dsi *dsi,
				       unsigned long timeout)
{
	timeout = jiffies + msecs_to_jiffies(250);

	while (time_before(jiffies, timeout)) {
		u32 value = tegra_dsi_readl(dsi, DSI_STATUS);
		u8 count = value & 0x1f;

		if (count > 0)
			return count;

		usleep_range(1000, 2000);
	}

	DRM_DEBUG_KMS("peripheral returned no data\n");
	return -ETIMEDOUT;
}