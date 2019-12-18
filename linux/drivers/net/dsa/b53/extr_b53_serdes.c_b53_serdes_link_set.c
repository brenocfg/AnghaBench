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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct b53_device {int dummy; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 scalar_t__ B53_INVALID_LANE ; 
 int /*<<< orphan*/  B53_SERDES_MII_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  SERDES_MII_BLK ; 
 scalar_t__ b53_serdes_map_lane (struct b53_device*,int) ; 
 int /*<<< orphan*/  b53_serdes_read (struct b53_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b53_serdes_write (struct b53_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b53_serdes_link_set(struct b53_device *dev, int port, unsigned int mode,
			 phy_interface_t interface, bool link_up)
{
	u8 lane = b53_serdes_map_lane(dev, port);
	u16 reg;

	if (lane == B53_INVALID_LANE)
		return;

	reg = b53_serdes_read(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			      SERDES_MII_BLK);
	if (link_up)
		reg &= ~BMCR_PDOWN;
	else
		reg |= BMCR_PDOWN;
	b53_serdes_write(dev, lane, B53_SERDES_MII_REG(MII_BMCR),
			 SERDES_MII_BLK, reg);
}