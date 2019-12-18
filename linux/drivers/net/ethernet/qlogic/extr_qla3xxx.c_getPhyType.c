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
typedef  int u16 ;
struct ql3_adapter {int /*<<< orphan*/  ndev; } ;
typedef  enum PHY_DEVICE_TYPE { ____Placeholder_PHY_DEVICE_TYPE } PHY_DEVICE_TYPE ;
struct TYPE_2__ {int phyIdOUI; int phyIdModel; int phyDevice; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int MAX_PHY_DEV_TYPES ; 
 TYPE_1__* PHY_DEVICES ; 
 int PHY_MODEL_MASK ; 
 int PHY_OUI_1_MASK ; 
 int PHY_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum PHY_DEVICE_TYPE getPhyType(struct ql3_adapter *qdev,
				       u16 phyIdReg0, u16 phyIdReg1)
{
	enum PHY_DEVICE_TYPE result = PHY_TYPE_UNKNOWN;
	u32   oui;
	u16   model;
	int i;

	if (phyIdReg0 == 0xffff)
		return result;

	if (phyIdReg1 == 0xffff)
		return result;

	/* oui is split between two registers */
	oui = (phyIdReg0 << 6) | ((phyIdReg1 & PHY_OUI_1_MASK) >> 10);

	model = (phyIdReg1 & PHY_MODEL_MASK) >> 4;

	/* Scan table for this PHY */
	for (i = 0; i < MAX_PHY_DEV_TYPES; i++) {
		if ((oui == PHY_DEVICES[i].phyIdOUI) &&
		    (model == PHY_DEVICES[i].phyIdModel)) {
			netdev_info(qdev->ndev, "Phy: %s\n",
				    PHY_DEVICES[i].name);
			result = PHY_DEVICES[i].phyDevice;
			break;
		}
	}

	return result;
}