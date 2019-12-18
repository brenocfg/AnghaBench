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
struct vortex_private {int /*<<< orphan*/  mii_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int MDIO_DATA_READ ; 
 int MDIO_DATA_WRITE0 ; 
 int MDIO_DATA_WRITE1 ; 
 int MDIO_ENB_IN ; 
 int MDIO_SHIFT_CLK ; 
 int /*<<< orphan*/  Wn4_PhysicalMgmt ; 
 int /*<<< orphan*/  mdio_delay (struct vortex_private*) ; 
 int /*<<< orphan*/  mdio_sync (struct vortex_private*,int) ; 
 scalar_t__ mii_preamble_required ; 
 struct vortex_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int window_read16 (struct vortex_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_write16 (struct vortex_private*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdio_read(struct net_device *dev, int phy_id, int location)
{
	int i;
	struct vortex_private *vp = netdev_priv(dev);
	int read_cmd = (0xf6 << 10) | (phy_id << 5) | location;
	unsigned int retval = 0;

	spin_lock_bh(&vp->mii_lock);

	if (mii_preamble_required)
		mdio_sync(vp, 32);

	/* Shift the read command bits out. */
	for (i = 14; i >= 0; i--) {
		int dataval = (read_cmd&(1<<i)) ? MDIO_DATA_WRITE1 : MDIO_DATA_WRITE0;
		window_write16(vp, dataval, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		window_write16(vp, dataval | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	}
	/* Read the two transition, 16 data, and wire-idle bits. */
	for (i = 19; i > 0; i--) {
		window_write16(vp, MDIO_ENB_IN, 4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
		retval = (retval << 1) |
			((window_read16(vp, 4, Wn4_PhysicalMgmt) &
			  MDIO_DATA_READ) ? 1 : 0);
		window_write16(vp, MDIO_ENB_IN | MDIO_SHIFT_CLK,
			       4, Wn4_PhysicalMgmt);
		mdio_delay(vp);
	}

	spin_unlock_bh(&vp->mii_lock);

	return retval & 0x20000 ? 0xffff : retval>>1 & 0xffff;
}