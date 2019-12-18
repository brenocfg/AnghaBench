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
typedef  int u16 ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct net_device {TYPE_2__ dev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  driver; } ;
struct ethsw_port_priv {TYPE_3__* ethsw_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  mc_io; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 char* KBUILD_MODNAME ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 int dpsw_get_api_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 struct ethsw_port_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ethsw_get_drvinfo(struct net_device *netdev,
			      struct ethtool_drvinfo *drvinfo)
{
	struct ethsw_port_priv *port_priv = netdev_priv(netdev);
	u16 version_major, version_minor;
	int err;

	strlcpy(drvinfo->driver, KBUILD_MODNAME, sizeof(drvinfo->driver));

	err = dpsw_get_api_version(port_priv->ethsw_data->mc_io, 0,
				   &version_major,
				   &version_minor);
	if (err)
		strlcpy(drvinfo->fw_version, "N/A",
			sizeof(drvinfo->fw_version));
	else
		snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
			 "%u.%u", version_major, version_minor);

	strlcpy(drvinfo->bus_info, dev_name(netdev->dev.parent->parent),
		sizeof(drvinfo->bus_info));
}