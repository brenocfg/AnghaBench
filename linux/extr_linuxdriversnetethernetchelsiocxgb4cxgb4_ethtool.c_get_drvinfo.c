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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_priv_flags; int /*<<< orphan*/  erom_version; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  regdump_len; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  tp_vers; int /*<<< orphan*/  fw_vers; } ;
struct adapter {TYPE_1__ params; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_BUILD_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MAJOR_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MICRO_G (int /*<<< orphan*/ ) ; 
 int FW_HDR_FW_VER_MINOR_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb4_driver_name ; 
 int /*<<< orphan*/  cxgb4_driver_version ; 
 int /*<<< orphan*/  cxgb4_priv_flags_strings ; 
 int /*<<< orphan*/  get_regs_len (struct net_device*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int,...) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_get_exprom_version (struct adapter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct adapter *adapter = netdev2adap(dev);
	u32 exprom_vers;

	strlcpy(info->driver, cxgb4_driver_name, sizeof(info->driver));
	strlcpy(info->version, cxgb4_driver_version,
		sizeof(info->version));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		sizeof(info->bus_info));
	info->regdump_len = get_regs_len(dev);

	if (!adapter->params.fw_vers)
		strcpy(info->fw_version, "N/A");
	else
		snprintf(info->fw_version, sizeof(info->fw_version),
			 "%u.%u.%u.%u, TP %u.%u.%u.%u",
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.fw_vers),
			 FW_HDR_FW_VER_MAJOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MINOR_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_MICRO_G(adapter->params.tp_vers),
			 FW_HDR_FW_VER_BUILD_G(adapter->params.tp_vers));

	if (!t4_get_exprom_version(adapter, &exprom_vers))
		snprintf(info->erom_version, sizeof(info->erom_version),
			 "%u.%u.%u.%u",
			 FW_HDR_FW_VER_MAJOR_G(exprom_vers),
			 FW_HDR_FW_VER_MINOR_G(exprom_vers),
			 FW_HDR_FW_VER_MICRO_G(exprom_vers),
			 FW_HDR_FW_VER_BUILD_G(exprom_vers));
	info->n_priv_flags = ARRAY_SIZE(cxgb4_priv_flags_strings);
}