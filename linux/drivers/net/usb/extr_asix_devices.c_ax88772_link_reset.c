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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int /*<<< orphan*/  net; int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {scalar_t__ duplex; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88772_MEDIUM_DEFAULT ; 
 int /*<<< orphan*/  AX_MEDIUM_FD ; 
 int /*<<< orphan*/  AX_MEDIUM_PS ; 
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int /*<<< orphan*/  mii_check_media (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax88772_link_reset(struct usbnet *dev)
{
	u16 mode;
	struct ethtool_cmd ecmd = { .cmd = ETHTOOL_GSET };

	mii_check_media(&dev->mii, 1, 1);
	mii_ethtool_gset(&dev->mii, &ecmd);
	mode = AX88772_MEDIUM_DEFAULT;

	if (ethtool_cmd_speed(&ecmd) != SPEED_100)
		mode &= ~AX_MEDIUM_PS;

	if (ecmd.duplex != DUPLEX_FULL)
		mode &= ~AX_MEDIUM_FD;

	netdev_dbg(dev->net, "ax88772_link_reset() speed: %u duplex: %d setting mode to 0x%04x\n",
		   ethtool_cmd_speed(&ecmd), ecmd.duplex, mode);

	asix_write_medium_mode(dev, mode, 0);

	return 0;
}