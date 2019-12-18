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
typedef  int u64 ;
typedef  int u32 ;
struct phy_device {struct adin_priv* priv; } ;
struct adin_priv {int* stats; } ;
struct adin_hw_stat {int reg1; } ;

/* Variables and functions */
 struct adin_hw_stat* adin_hw_stats ; 
 int adin_read_mmd_stat_regs (struct phy_device*,struct adin_hw_stat*,int*) ; 
 int phy_read (struct phy_device*,int) ; 

__attribute__((used)) static u64 adin_get_stat(struct phy_device *phydev, int i)
{
	struct adin_hw_stat *stat = &adin_hw_stats[i];
	struct adin_priv *priv = phydev->priv;
	u32 val;
	int ret;

	if (stat->reg1 > 0x1f) {
		ret = adin_read_mmd_stat_regs(phydev, stat, &val);
		if (ret < 0)
			return (u64)(~0);
	} else {
		ret = phy_read(phydev, stat->reg1);
		if (ret < 0)
			return (u64)(~0);
		val = (ret & 0xffff);
	}

	priv->stats[i] += val;

	return priv->stats[i];
}