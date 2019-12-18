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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct usbnet {struct aqc111_data* driver_priv; } ;
struct aqc111_data {int phy_cfg; } ;

/* Variables and functions */
 int AQ_ADV_100M ; 
 int AQ_ADV_1G ; 
 int AQ_ADV_2G5 ; 
 int AQ_ADV_5G ; 
 int AQ_ADV_MASK ; 
 int AQ_ASYM_PAUSE ; 
 int AQ_DOWNSHIFT ; 
 int AQ_DSH_RETRIES_MASK ; 
 int AQ_DSH_RETRIES_SHIFT ; 
 int AQ_PAUSE ; 
 int /*<<< orphan*/  AQ_PHY_OPS ; 
 scalar_t__ AUTONEG_ENABLE ; 
#define  SPEED_100 131 
#define  SPEED_1000 130 
#define  SPEED_2500 129 
#define  SPEED_5000 128 
 int /*<<< orphan*/  aqc111_write32_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void aqc111_set_phy_speed(struct usbnet *dev, u8 autoneg, u16 speed)
{
	struct aqc111_data *aqc111_data = dev->driver_priv;

	aqc111_data->phy_cfg &= ~AQ_ADV_MASK;
	aqc111_data->phy_cfg |= AQ_PAUSE;
	aqc111_data->phy_cfg |= AQ_ASYM_PAUSE;
	aqc111_data->phy_cfg |= AQ_DOWNSHIFT;
	aqc111_data->phy_cfg &= ~AQ_DSH_RETRIES_MASK;
	aqc111_data->phy_cfg |= (3 << AQ_DSH_RETRIES_SHIFT) &
				AQ_DSH_RETRIES_MASK;

	if (autoneg == AUTONEG_ENABLE) {
		switch (speed) {
		case SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			/* fall-through */
		case SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			/* fall-through */
		case SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			/* fall-through */
		case SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			/* fall-through */
		}
	} else {
		switch (speed) {
		case SPEED_5000:
			aqc111_data->phy_cfg |= AQ_ADV_5G;
			break;
		case SPEED_2500:
			aqc111_data->phy_cfg |= AQ_ADV_2G5;
			break;
		case SPEED_1000:
			aqc111_data->phy_cfg |= AQ_ADV_1G;
			break;
		case SPEED_100:
			aqc111_data->phy_cfg |= AQ_ADV_100M;
			break;
		}
	}

	aqc111_write32_cmd(dev, AQ_PHY_OPS, 0, 0, &aqc111_data->phy_cfg);
}