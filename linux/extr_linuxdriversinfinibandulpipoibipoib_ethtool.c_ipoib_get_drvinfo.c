#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ipoib_dev_priv {TYPE_2__* ca; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 char* dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_get_device_fw_str (TYPE_2__*,int /*<<< orphan*/ ) ; 
 char* ipoib_driver_version ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void ipoib_get_drvinfo(struct net_device *netdev,
			      struct ethtool_drvinfo *drvinfo)
{
	struct ipoib_dev_priv *priv = ipoib_priv(netdev);

	ib_get_device_fw_str(priv->ca, drvinfo->fw_version);

	strlcpy(drvinfo->bus_info, dev_name(priv->ca->dev.parent),
		sizeof(drvinfo->bus_info));

	strlcpy(drvinfo->version, ipoib_driver_version,
		sizeof(drvinfo->version));

	strlcpy(drvinfo->driver, "ib_ipoib", sizeof(drvinfo->driver));
}