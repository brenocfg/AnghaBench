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
struct mt76x02_dev {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TX_ALC_CFG_1 ; 
 int /*<<< orphan*/  MT_TX_ALC_CFG_1_TEMP_COMP ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x0_phy_get_delta_power (struct mt76x02_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x0_phy_get_target_power (struct mt76x02_dev*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mt76x0_phy_tssi_adc_calibrate (struct mt76x02_dev*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void mt76x0_phy_tssi_calibrate(struct mt76x02_dev *dev)
{
	s8 target_power, target_pa_power;
	u8 tssi_info[3], tx_mode;
	s16 ltssi;
	s8 val;

	if (mt76x0_phy_tssi_adc_calibrate(dev, &ltssi, tssi_info) < 0)
		return;

	tx_mode = tssi_info[0] & 0x7;
	if (mt76x0_phy_get_target_power(dev, tx_mode, tssi_info,
					&target_power, &target_pa_power) < 0)
		return;

	val = mt76x0_phy_get_delta_power(dev, tx_mode, target_power,
					 target_pa_power, ltssi);
	mt76_rmw_field(dev, MT_TX_ALC_CFG_1, MT_TX_ALC_CFG_1_TEMP_COMP, val);
}