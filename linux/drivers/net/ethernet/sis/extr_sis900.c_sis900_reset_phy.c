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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CNTL_RESET ; 
 int /*<<< orphan*/  MII_CONTROL ; 
 int /*<<< orphan*/  MII_STATUS ; 
 int /*<<< orphan*/  mdio_read (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 sis900_reset_phy(struct net_device *net_dev, int phy_addr)
{
	int i;
	u16 status;

	for (i = 0; i < 2; i++)
		status = mdio_read(net_dev, phy_addr, MII_STATUS);

	mdio_write( net_dev, phy_addr, MII_CONTROL, MII_CNTL_RESET );

	return status;
}