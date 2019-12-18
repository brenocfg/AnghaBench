#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  tprev; int /*<<< orphan*/  fwrev; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct adapter {TYPE_3__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_VERSION ; 
 int FW_HDR_FW_VER_BUILD_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MAJOR_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MICRO_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MINOR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cxgb4vf_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *drvinfo)
{
	struct adapter *adapter = netdev2adap(dev);

	strlcpy(drvinfo->driver, KBUILD_MODNAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, DRV_VERSION, sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, pci_name(to_pci_dev(dev->dev.parent)),
		sizeof(drvinfo->bus_info));
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "%u.%u.%u.%u, TP %u.%u.%u.%u",
		 FW_HDR_FW_VER_MAJOR_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MINOR_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MICRO_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_BUILD_G(adapter->params.dev.fwrev),
		 FW_HDR_FW_VER_MAJOR_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_MINOR_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_MICRO_G(adapter->params.dev.tprev),
		 FW_HDR_FW_VER_BUILD_G(adapter->params.dev.tprev));
}