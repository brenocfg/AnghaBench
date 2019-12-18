#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {TYPE_2__* net; struct ax88172a_private* driver_priv; int /*<<< orphan*/  data; } ;
struct ax88172a_private {int phy_name; int /*<<< orphan*/  phydev; int /*<<< orphan*/  phy_addr; TYPE_1__* mdio; int /*<<< orphan*/  use_embdphy; } ;
struct asix_data {int /*<<< orphan*/ * mac_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int AX88772_IPG0_DEFAULT ; 
 int AX88772_IPG1_DEFAULT ; 
 int /*<<< orphan*/  AX88772_IPG2_DEFAULT ; 
 int /*<<< orphan*/  AX_CMD_WRITE_IPG0 ; 
 int /*<<< orphan*/  AX_CMD_WRITE_NODE_ID ; 
 int AX_DEFAULT_RX_CTL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 char* PHY_ID_FMT ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_read_medium_status (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asix_read_rx_ctl (struct usbnet*,int /*<<< orphan*/ ) ; 
 int asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int asix_write_rx_ctl (struct usbnet*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ax88172a_adjust_link ; 
 int /*<<< orphan*/  ax88172a_reset_phy (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genphy_resume (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  phy_connect (TYPE_2__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax88172a_reset(struct usbnet *dev)
{
	struct asix_data *data = (struct asix_data *)&dev->data;
	struct ax88172a_private *priv = dev->driver_priv;
	int ret;
	u16 rx_ctl;

	ax88172a_reset_phy(dev, priv->use_embdphy);

	msleep(150);
	rx_ctl = asix_read_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after software reset\n", rx_ctl);
	ret = asix_write_rx_ctl(dev, 0x0000, 0);
	if (ret < 0)
		goto out;

	rx_ctl = asix_read_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x setting to 0x0000\n", rx_ctl);

	msleep(150);

	ret = asix_write_cmd(dev, AX_CMD_WRITE_IPG0,
			     AX88772_IPG0_DEFAULT | AX88772_IPG1_DEFAULT,
			     AX88772_IPG2_DEFAULT, 0, NULL, 0);
	if (ret < 0) {
		netdev_err(dev->net, "Write IPG,IPG1,IPG2 failed: %d\n", ret);
		goto out;
	}

	/* Rewrite MAC address */
	memcpy(data->mac_addr, dev->net->dev_addr, ETH_ALEN);
	ret = asix_write_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0, ETH_ALEN,
			     data->mac_addr, 0);
	if (ret < 0)
		goto out;

	/* Set RX_CTL to default values with 2k buffer, and enable cactus */
	ret = asix_write_rx_ctl(dev, AX_DEFAULT_RX_CTL, 0);
	if (ret < 0)
		goto out;

	rx_ctl = asix_read_rx_ctl(dev, 0);
	netdev_dbg(dev->net, "RX_CTL is 0x%04x after all initializations\n",
		   rx_ctl);

	rx_ctl = asix_read_medium_status(dev, 0);
	netdev_dbg(dev->net, "Medium Status is 0x%04x after all initializations\n",
		   rx_ctl);

	/* Connect to PHY */
	snprintf(priv->phy_name, 20, PHY_ID_FMT,
		 priv->mdio->id, priv->phy_addr);

	priv->phydev = phy_connect(dev->net, priv->phy_name,
				   &ax88172a_adjust_link,
				   PHY_INTERFACE_MODE_MII);
	if (IS_ERR(priv->phydev)) {
		netdev_err(dev->net, "Could not connect to PHY device %s\n",
			   priv->phy_name);
		ret = PTR_ERR(priv->phydev);
		goto out;
	}

	netdev_info(dev->net, "Connected to phy %s\n", priv->phy_name);

	/* During power-up, the AX88172A set the power down (BMCR_PDOWN)
	 * bit of the PHY. Bring the PHY up again.
	 */
	genphy_resume(priv->phydev);
	phy_start(priv->phydev);

	return 0;

out:
	return ret;

}