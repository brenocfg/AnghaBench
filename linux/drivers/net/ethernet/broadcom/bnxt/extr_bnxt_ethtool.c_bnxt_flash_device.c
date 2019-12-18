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
struct net_device {int dummy; } ;
struct ethtool_flash {int region; int /*<<< orphan*/  data; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_PF (struct bnxt*) ; 
 int EINVAL ; 
 int ETHTOOL_FLASH_ALL_REGIONS ; 
 int bnxt_flash_firmware_from_file (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int bnxt_flash_package_from_file (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_flash_device(struct net_device *dev,
			     struct ethtool_flash *flash)
{
	if (!BNXT_PF((struct bnxt *)netdev_priv(dev))) {
		netdev_err(dev, "flashdev not supported from a virtual function\n");
		return -EINVAL;
	}

	if (flash->region == ETHTOOL_FLASH_ALL_REGIONS ||
	    flash->region > 0xffff)
		return bnxt_flash_package_from_file(dev, flash->data,
						    flash->region);

	return bnxt_flash_firmware_from_file(dev, flash->region, flash->data);
}