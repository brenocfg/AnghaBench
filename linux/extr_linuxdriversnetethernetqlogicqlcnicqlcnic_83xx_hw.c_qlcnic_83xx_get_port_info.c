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
struct qlcnic_hardware_context {int port_config; int /*<<< orphan*/  link_autoneg; void* port_type; } ;
struct qlcnic_adapter {TYPE_1__* pdev; struct qlcnic_hardware_context* ahw; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 void* QLCNIC_GBE ; 
 void* QLCNIC_XGBE ; 
 int QLC_83XX_100_CAPABLE ; 
 int QLC_83XX_10G_CAPABLE ; 
 int QLC_83XX_10_CAPABLE ; 
 int QLC_83XX_1G_CAPABLE ; 
 scalar_t__ QLC_83XX_AUTONEG (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int qlcnic_83xx_get_port_config (struct qlcnic_adapter*) ; 

int qlcnic_83xx_get_port_info(struct qlcnic_adapter *adapter)
{
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int status;

	status = qlcnic_83xx_get_port_config(adapter);
	if (status) {
		dev_err(&adapter->pdev->dev,
			"Get Port Info failed\n");
	} else {

		if (ahw->port_config & QLC_83XX_10G_CAPABLE) {
			ahw->port_type = QLCNIC_XGBE;
		} else if (ahw->port_config & QLC_83XX_10_CAPABLE ||
			   ahw->port_config & QLC_83XX_100_CAPABLE ||
			   ahw->port_config & QLC_83XX_1G_CAPABLE) {
			ahw->port_type = QLCNIC_GBE;
		} else {
			ahw->port_type = QLCNIC_XGBE;
		}

		if (QLC_83XX_AUTONEG(ahw->port_config))
			ahw->link_autoneg = AUTONEG_ENABLE;

	}
	return status;
}