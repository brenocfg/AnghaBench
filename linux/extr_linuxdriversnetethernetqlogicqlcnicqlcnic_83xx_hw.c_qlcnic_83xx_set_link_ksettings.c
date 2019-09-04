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
typedef  int u32 ;
struct qlcnic_hardware_context {int port_config; } ;
struct qlcnic_adapter {int /*<<< orphan*/  netdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {scalar_t__ duplex; int speed; scalar_t__ autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int QLC_83XX_100_CAPABLE ; 
 int QLC_83XX_10G_CAPABLE ; 
 int QLC_83XX_10_CAPABLE ; 
 int QLC_83XX_1G_CAPABLE ; 
 int QLC_83XX_AUTONEG_ENABLE ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_10000 128 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 
 int qlcnic_83xx_set_port_config (struct qlcnic_adapter*) ; 

int qlcnic_83xx_set_link_ksettings(struct qlcnic_adapter *adapter,
				   const struct ethtool_link_ksettings *ecmd)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	u32 config = adapter->ahw->port_config;
	int status = 0;

	/* 83xx devices do not support Half duplex */
	if (ecmd->base.duplex == DUPLEX_HALF) {
		netdev_info(adapter->netdev,
			    "Half duplex mode not supported\n");
		return -EINVAL;
	}

	if (ecmd->base.autoneg) {
		ahw->port_config |= QLC_83XX_AUTONEG_ENABLE;
		ahw->port_config |= (QLC_83XX_100_CAPABLE |
				     QLC_83XX_1G_CAPABLE |
				     QLC_83XX_10G_CAPABLE);
	} else { /* force speed */
		ahw->port_config &= ~QLC_83XX_AUTONEG_ENABLE;
		switch (ecmd->base.speed) {
		case SPEED_10:
			ahw->port_config &= ~(QLC_83XX_100_CAPABLE |
					      QLC_83XX_1G_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_10_CAPABLE;
			break;
		case SPEED_100:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_1G_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_100_CAPABLE;
			break;
		case SPEED_1000:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_100_CAPABLE |
					      QLC_83XX_10G_CAPABLE);
			ahw->port_config |= QLC_83XX_1G_CAPABLE;
			break;
		case SPEED_10000:
			ahw->port_config &= ~(QLC_83XX_10_CAPABLE |
					      QLC_83XX_100_CAPABLE |
					      QLC_83XX_1G_CAPABLE);
			ahw->port_config |= QLC_83XX_10G_CAPABLE;
			break;
		default:
			return -EINVAL;
		}
	}
	status = qlcnic_83xx_set_port_config(adapter);
	if (status) {
		netdev_info(adapter->netdev,
			    "Failed to Set Link Speed and autoneg.\n");
		ahw->port_config = config;
	}

	return status;
}