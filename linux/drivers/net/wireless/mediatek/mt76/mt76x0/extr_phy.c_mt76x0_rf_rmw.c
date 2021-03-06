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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mt76x02_dev {int dummy; } ;

/* Variables and functions */
 int mt76x0_rf_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int mt76x0_rf_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x0_rf_rmw(struct mt76x02_dev *dev, u32 offset, u8 mask, u8 val)
{
	int ret;

	ret = mt76x0_rf_rr(dev, offset);
	if (ret < 0)
		return ret;

	val |= ret & ~mask;

	ret = mt76x0_rf_wr(dev, offset, val);
	return ret ? ret : val;
}