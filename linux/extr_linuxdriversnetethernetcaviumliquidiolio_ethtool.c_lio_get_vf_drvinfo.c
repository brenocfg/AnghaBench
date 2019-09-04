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
struct TYPE_2__ {int /*<<< orphan*/  liquidio_firmware_version; } ;
struct octeon_device {int /*<<< orphan*/  pci_dev; TYPE_1__ fw_info; } ;
struct net_device {int dummy; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ETHTOOL_FWVERS_LEN ; 
 struct lio* GET_LIO (struct net_device*) ; 
 char* LIQUIDIO_VERSION ; 
 int /*<<< orphan*/  memset (struct ethtool_drvinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
lio_get_vf_drvinfo(struct net_device *netdev, struct ethtool_drvinfo *drvinfo)
{
	struct octeon_device *oct;
	struct lio *lio;

	lio = GET_LIO(netdev);
	oct = lio->oct_dev;

	memset(drvinfo, 0, sizeof(struct ethtool_drvinfo));
	strcpy(drvinfo->driver, "liquidio_vf");
	strcpy(drvinfo->version, LIQUIDIO_VERSION);
	strncpy(drvinfo->fw_version, oct->fw_info.liquidio_firmware_version,
		ETHTOOL_FWVERS_LEN);
	strncpy(drvinfo->bus_info, pci_name(oct->pci_dev), 32);
}