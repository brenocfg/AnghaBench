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
struct phy_device {int dummy; } ;
struct bcm_phy_hw_stat {int shift; int bits; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int U64_MAX ; 
 struct bcm_phy_hw_stat* bcm_phy_hw_stats ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 bcm_phy_get_stat(struct phy_device *phydev, u64 *shadow,
			    unsigned int i)
{
	struct bcm_phy_hw_stat stat = bcm_phy_hw_stats[i];
	int val;
	u64 ret;

	val = phy_read(phydev, stat.reg);
	if (val < 0) {
		ret = U64_MAX;
	} else {
		val >>= stat.shift;
		val = val & ((1 << stat.bits) - 1);
		shadow[i] += val;
		ret = shadow[i];
	}

	return ret;
}