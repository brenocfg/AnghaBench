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
struct usbnet {struct aqc111_data* driver_priv; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int eedump_len; int regdump_len; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {int major; int minor; int rev; } ;
struct aqc111_data {TYPE_1__ fw_ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 struct usbnet* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbnet_get_drvinfo (struct net_device*,struct ethtool_drvinfo*) ; 

__attribute__((used)) static void aqc111_get_drvinfo(struct net_device *net,
			       struct ethtool_drvinfo *info)
{
	struct usbnet *dev = netdev_priv(net);
	struct aqc111_data *aqc111_data = dev->driver_priv;

	/* Inherit standard device info */
	usbnet_get_drvinfo(net, info);
	strlcpy(info->driver, DRIVER_NAME, sizeof(info->driver));
	snprintf(info->fw_version, sizeof(info->fw_version), "%u.%u.%u",
		 aqc111_data->fw_ver.major,
		 aqc111_data->fw_ver.minor,
		 aqc111_data->fw_ver.rev);
	info->eedump_len = 0x00;
	info->regdump_len = 0x00;
}