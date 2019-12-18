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
struct mii_if_info {int phy_id_mask; int reg_num_mask; scalar_t__ phy_id; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_enetsw_mii_mdio_read ; 
 int /*<<< orphan*/  bcm_enetsw_mii_mdio_write ; 
 int generic_mii_ioctl (struct mii_if_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 

__attribute__((used)) static int bcm_enetsw_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct mii_if_info mii;

	mii.dev = dev;
	mii.mdio_read = bcm_enetsw_mii_mdio_read;
	mii.mdio_write = bcm_enetsw_mii_mdio_write;
	mii.phy_id = 0;
	mii.phy_id_mask = 0x3f;
	mii.reg_num_mask = 0x1f;
	return generic_mii_ioctl(&mii, if_mii(rq), cmd, NULL);

}