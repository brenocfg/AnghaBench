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
struct smsc_hw_stat {int /*<<< orphan*/  reg; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int U64_MAX ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 struct smsc_hw_stat* smsc_hw_stats ; 

__attribute__((used)) static u64 smsc_get_stat(struct phy_device *phydev, int i)
{
	struct smsc_hw_stat stat = smsc_hw_stats[i];
	int val;
	u64 ret;

	val = phy_read(phydev, stat.reg);
	if (val < 0)
		ret = U64_MAX;
	else
		ret = val;

	return ret;
}