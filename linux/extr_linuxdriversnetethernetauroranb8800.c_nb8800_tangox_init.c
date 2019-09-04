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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct nb8800_priv {int phy_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NB8800_TANGOX_PAD_MODE ; 
 int /*<<< orphan*/  PAD_MODE_MII ; 
 int /*<<< orphan*/  PAD_MODE_RGMII ; 
#define  PHY_INTERFACE_MODE_GMII 133 
#define  PHY_INTERFACE_MODE_MII 132 
#define  PHY_INTERFACE_MODE_RGMII 131 
#define  PHY_INTERFACE_MODE_RGMII_ID 130 
#define  PHY_INTERFACE_MODE_RGMII_RXID 129 
#define  PHY_INTERFACE_MODE_RGMII_TXID 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb8800_writeb (struct nb8800_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_modes (int) ; 

__attribute__((used)) static int nb8800_tangox_init(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	u32 pad_mode = PAD_MODE_MII;

	switch (priv->phy_mode) {
	case PHY_INTERFACE_MODE_MII:
	case PHY_INTERFACE_MODE_GMII:
		pad_mode = PAD_MODE_MII;
		break;

	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_TXID:
		pad_mode = PAD_MODE_RGMII;
		break;

	default:
		dev_err(dev->dev.parent, "unsupported phy mode %s\n",
			phy_modes(priv->phy_mode));
		return -EINVAL;
	}

	nb8800_writeb(priv, NB8800_TANGOX_PAD_MODE, pad_mode);

	return 0;
}