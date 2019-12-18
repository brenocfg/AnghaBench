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
typedef  int /*<<< orphan*/  u64 ;
struct phy_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int marvell_get_sset_count (struct phy_device*) ; 
 int /*<<< orphan*/  marvell_get_stat (struct phy_device*,int) ; 

__attribute__((used)) static void marvell_get_stats(struct phy_device *phydev,
			      struct ethtool_stats *stats, u64 *data)
{
	int count = marvell_get_sset_count(phydev);
	int i;

	for (i = 0; i < count; i++)
		data[i] = marvell_get_stat(phydev, i);
}