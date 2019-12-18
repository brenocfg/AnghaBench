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
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {int /*<<< orphan*/  duplex; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm9601_link_reset(struct usbnet *dev)
{
	struct ethtool_cmd ecmd = { .cmd = ETHTOOL_GSET };

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);

	netdev_dbg(dev->net, "link_reset() speed: %u duplex: %d\n",
		   ethtool_cmd_speed(&ecmd), ecmd.duplex);

	return 0;
}