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
struct phy_device {int speed; } ;
struct net_device {struct phy_device* phydev; } ;
struct gfar_private {struct net_device* ndev; } ;

/* Variables and functions */
 unsigned int GFAR_100_TIME ; 
 unsigned int GFAR_10_TIME ; 
 unsigned int GFAR_GBIT_TIME ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 

__attribute__((used)) static unsigned int gfar_usecs2ticks(struct gfar_private *priv,
				     unsigned int usecs)
{
	struct net_device *ndev = priv->ndev;
	struct phy_device *phydev = ndev->phydev;
	unsigned int count;

	/* The timer is different, depending on the interface speed */
	switch (phydev->speed) {
	case SPEED_1000:
		count = GFAR_GBIT_TIME;
		break;
	case SPEED_100:
		count = GFAR_100_TIME;
		break;
	case SPEED_10:
	default:
		count = GFAR_10_TIME;
		break;
	}

	/* Make sure we return a number greater than 0
	 * if usecs > 0 */
	return (usecs * 1000 + count - 1) / count;
}