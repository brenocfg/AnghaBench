#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mt76x2_temp_comp {int high_slope; int low_slope; int /*<<< orphan*/  lower_bound; int /*<<< orphan*/  upper_bound; scalar_t__ temp_25_ref; } ;
struct TYPE_2__ {int temp; } ;
struct mt76x02_dev {TYPE_1__ cal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TEMP_SENSOR ; 
 int /*<<< orphan*/  MT_TEMP_SENSOR_VAL ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1_TEMP_COMP ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_2 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_2_TEMP_COMP ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mt76x2_get_temp_comp (struct mt76x02_dev*,struct mt76x2_temp_comp*) ; 

__attribute__((used)) static void
mt76x2_phy_temp_compensate(struct mt76x02_dev *dev)
{
	struct mt76x2_temp_comp t;
	int temp, db_diff;

	if (mt76x2_get_temp_comp(dev, &t))
		return;

	temp = mt76_get_field(dev, MT_TEMP_SENSOR, MT_TEMP_SENSOR_VAL);
	temp -= t.temp_25_ref;
	temp = (temp * 1789) / 1000 + 25;
	dev->cal.temp = temp;

	if (temp > 25)
		db_diff = (temp - 25) / t.high_slope;
	else
		db_diff = (25 - temp) / t.low_slope;

	db_diff = min(db_diff, t.upper_bound);
	db_diff = max(db_diff, t.lower_bound);

	mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP,
		       db_diff * 2);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_2, MT_TX_ALC_CFG_2_TEMP_COMP,
		       db_diff * 2);
}