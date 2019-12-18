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
typedef  void* u32 ;
struct net_device {int dummy; } ;
struct hip04_priv {int phy_mode; scalar_t__ base; void* duplex; void* speed; } ;

/* Variables and functions */
 void* GE_DUPLEX_FULL ; 
 void* GE_DUPLEX_HALF ; 
 scalar_t__ GE_DUPLEX_TYPE ; 
 void* GE_MODE_CHANGE_EN ; 
 scalar_t__ GE_MODE_CHANGE_REG ; 
 scalar_t__ GE_PORT_MODE ; 
 void* MII_SPEED_10 ; 
 void* MII_SPEED_100 ; 
#define  PHY_INTERFACE_MODE_MII 129 
#define  PHY_INTERFACE_MODE_SGMII 128 
 void* SGMII_SPEED_10 ; 
 void* SGMII_SPEED_100 ; 
 void* SGMII_SPEED_1000 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 struct hip04_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  writel_relaxed (void*,scalar_t__) ; 

__attribute__((used)) static void hip04_config_port(struct net_device *ndev, u32 speed, u32 duplex)
{
	struct hip04_priv *priv = netdev_priv(ndev);
	u32 val;

	priv->speed = speed;
	priv->duplex = duplex;

	switch (priv->phy_mode) {
	case PHY_INTERFACE_MODE_SGMII:
		if (speed == SPEED_1000)
			val = SGMII_SPEED_1000;
		else if (speed == SPEED_100)
			val = SGMII_SPEED_100;
		else
			val = SGMII_SPEED_10;
		break;
	case PHY_INTERFACE_MODE_MII:
		if (speed == SPEED_100)
			val = MII_SPEED_100;
		else
			val = MII_SPEED_10;
		break;
	default:
		netdev_warn(ndev, "not supported mode\n");
		val = MII_SPEED_10;
		break;
	}
	writel_relaxed(val, priv->base + GE_PORT_MODE);

	val = duplex ? GE_DUPLEX_FULL : GE_DUPLEX_HALF;
	writel_relaxed(val, priv->base + GE_DUPLEX_TYPE);

	val = GE_MODE_CHANGE_EN;
	writel_relaxed(val, priv->base + GE_MODE_CHANGE_REG);
}