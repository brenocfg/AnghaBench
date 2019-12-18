#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct phy_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_3__ {int mask; int off; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int U64_MAX ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* tja11xx_hw_stats ; 

__attribute__((used)) static void tja11xx_get_stats(struct phy_device *phydev,
			      struct ethtool_stats *stats, u64 *data)
{
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(tja11xx_hw_stats); i++) {
		ret = phy_read(phydev, tja11xx_hw_stats[i].reg);
		if (ret < 0)
			data[i] = U64_MAX;
		else {
			data[i] = ret & tja11xx_hw_stats[i].mask;
			data[i] >>= tja11xx_hw_stats[i].off;
		}
	}
}