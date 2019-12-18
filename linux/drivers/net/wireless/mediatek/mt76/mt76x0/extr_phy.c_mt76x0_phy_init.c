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
struct mt76x02_dev {int /*<<< orphan*/  cal_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_phy_set_rxpath (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x02_phy_set_txdac (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_phy_ant_select (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x0_phy_calibration_work ; 
 int /*<<< orphan*/  mt76x0_phy_rf_init (struct mt76x02_dev*) ; 

void mt76x0_phy_init(struct mt76x02_dev *dev)
{
	INIT_DELAYED_WORK(&dev->cal_work, mt76x0_phy_calibration_work);

	mt76x0_phy_ant_select(dev);
	mt76x0_phy_rf_init(dev);
	mt76x02_phy_set_rxpath(dev);
	mt76x02_phy_set_txdac(dev);
}