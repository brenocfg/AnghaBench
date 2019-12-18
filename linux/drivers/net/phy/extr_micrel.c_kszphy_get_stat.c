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
struct phy_device {struct kszphy_priv* priv; } ;
struct kszphy_priv {int* stats; } ;
struct kszphy_hw_stat {int bits; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int U64_MAX ; 
 struct kszphy_hw_stat* kszphy_hw_stats ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 kszphy_get_stat(struct phy_device *phydev, int i)
{
	struct kszphy_hw_stat stat = kszphy_hw_stats[i];
	struct kszphy_priv *priv = phydev->priv;
	int val;
	u64 ret;

	val = phy_read(phydev, stat.reg);
	if (val < 0) {
		ret = U64_MAX;
	} else {
		val = val & ((1 << stat.bits) - 1);
		priv->stats[i] += val;
		ret = priv->stats[i];
	}

	return ret;
}