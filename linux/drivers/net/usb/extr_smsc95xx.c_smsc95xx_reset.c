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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct usbnet {int rx_urb_size; TYPE_2__* net; TYPE_1__* udev; scalar_t__* data; } ;
struct smsc95xx_priv {int mac_cr; } ;
struct TYPE_7__ {int /*<<< orphan*/  features; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_6__ {scalar_t__ speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFC_CFG ; 
 int AFC_CFG_DEFAULT ; 
 int /*<<< orphan*/  BULK_IN_DLY ; 
 int /*<<< orphan*/  BURST_CAP ; 
 int DEFAULT_BULK_IN_DELAY ; 
 int DEFAULT_FS_BURST_CAP_SIZE ; 
 int DEFAULT_HS_BURST_CAP_SIZE ; 
 scalar_t__ ETH_P_8021Q ; 
 int /*<<< orphan*/  FLOW ; 
 int FS_USB_PKT_SIZE ; 
 int HS_USB_PKT_SIZE ; 
 int /*<<< orphan*/  HW_CFG ; 
 int HW_CFG_BCE_ ; 
 int HW_CFG_BIR_ ; 
 int HW_CFG_LRST_ ; 
 int HW_CFG_MEF_ ; 
 int HW_CFG_RXDOFF_ ; 
 int /*<<< orphan*/  ID_REV ; 
 int /*<<< orphan*/  INT_EP_CTL ; 
 int INT_EP_CTL_PHY_INT_ ; 
 int /*<<< orphan*/  INT_STS ; 
 int INT_STS_CLEAR_ALL_ ; 
 int /*<<< orphan*/  LED_GPIO_CFG ; 
 int LED_GPIO_CFG_FDX_LED ; 
 int LED_GPIO_CFG_LNK_LED ; 
 int LED_GPIO_CFG_SPD_LED ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAX_SINGLE_PACKET_SIZE ; 
 int NET_IP_ALIGN ; 
 int PM_CTL_PHY_RST_ ; 
 int /*<<< orphan*/  PM_CTRL ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  VLAN1 ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netif_dbg (struct usbnet*,int /*<<< orphan*/ ,TYPE_2__*,char*,...) ; 
 int smsc95xx_phy_initialize (struct usbnet*) ; 
 int smsc95xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int smsc95xx_set_features (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int smsc95xx_set_mac_address (struct usbnet*) ; 
 int /*<<< orphan*/  smsc95xx_set_multicast (TYPE_2__*) ; 
 int smsc95xx_start_rx_path (struct usbnet*,int /*<<< orphan*/ ) ; 
 int smsc95xx_start_tx_path (struct usbnet*) ; 
 int smsc95xx_write_reg (struct usbnet*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ turbo_mode ; 

__attribute__((used)) static int smsc95xx_reset(struct usbnet *dev)
{
	struct smsc95xx_priv *pdata = (struct smsc95xx_priv *)(dev->data[0]);
	u32 read_buf, write_buf, burst_cap;
	int ret = 0, timeout;

	netif_dbg(dev, ifup, dev->net, "entering smsc95xx_reset\n");

	ret = smsc95xx_write_reg(dev, HW_CFG, HW_CFG_LRST_);
	if (ret < 0)
		return ret;

	timeout = 0;
	do {
		msleep(10);
		ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
		if (ret < 0)
			return ret;
		timeout++;
	} while ((read_buf & HW_CFG_LRST_) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout waiting for completion of Lite Reset\n");
		return ret;
	}

	ret = smsc95xx_write_reg(dev, PM_CTRL, PM_CTL_PHY_RST_);
	if (ret < 0)
		return ret;

	timeout = 0;
	do {
		msleep(10);
		ret = smsc95xx_read_reg(dev, PM_CTRL, &read_buf);
		if (ret < 0)
			return ret;
		timeout++;
	} while ((read_buf & PM_CTL_PHY_RST_) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout waiting for PHY Reset\n");
		return ret;
	}

	ret = smsc95xx_set_mac_address(dev);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net, "MAC Address: %pM\n",
		  dev->net->dev_addr);

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net, "Read Value from HW_CFG : 0x%08x\n",
		  read_buf);

	read_buf |= HW_CFG_BIR_;

	ret = smsc95xx_write_reg(dev, HW_CFG, read_buf);
	if (ret < 0)
		return ret;

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net,
		  "Read Value from HW_CFG after writing HW_CFG_BIR_: 0x%08x\n",
		  read_buf);

	if (!turbo_mode) {
		burst_cap = 0;
		dev->rx_urb_size = MAX_SINGLE_PACKET_SIZE;
	} else if (dev->udev->speed == USB_SPEED_HIGH) {
		burst_cap = DEFAULT_HS_BURST_CAP_SIZE / HS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_HS_BURST_CAP_SIZE;
	} else {
		burst_cap = DEFAULT_FS_BURST_CAP_SIZE / FS_USB_PKT_SIZE;
		dev->rx_urb_size = DEFAULT_FS_BURST_CAP_SIZE;
	}

	netif_dbg(dev, ifup, dev->net, "rx_urb_size=%ld\n",
		  (ulong)dev->rx_urb_size);

	ret = smsc95xx_write_reg(dev, BURST_CAP, burst_cap);
	if (ret < 0)
		return ret;

	ret = smsc95xx_read_reg(dev, BURST_CAP, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net,
		  "Read Value from BURST_CAP after writing: 0x%08x\n",
		  read_buf);

	ret = smsc95xx_write_reg(dev, BULK_IN_DLY, DEFAULT_BULK_IN_DELAY);
	if (ret < 0)
		return ret;

	ret = smsc95xx_read_reg(dev, BULK_IN_DLY, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net,
		  "Read Value from BULK_IN_DLY after writing: 0x%08x\n",
		  read_buf);

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net, "Read Value from HW_CFG: 0x%08x\n",
		  read_buf);

	if (turbo_mode)
		read_buf |= (HW_CFG_MEF_ | HW_CFG_BCE_);

	read_buf &= ~HW_CFG_RXDOFF_;

	/* set Rx data offset=2, Make IP header aligns on word boundary. */
	read_buf |= NET_IP_ALIGN << 9;

	ret = smsc95xx_write_reg(dev, HW_CFG, read_buf);
	if (ret < 0)
		return ret;

	ret = smsc95xx_read_reg(dev, HW_CFG, &read_buf);
	if (ret < 0)
		return ret;

	netif_dbg(dev, ifup, dev->net,
		  "Read Value from HW_CFG after writing: 0x%08x\n", read_buf);

	ret = smsc95xx_write_reg(dev, INT_STS, INT_STS_CLEAR_ALL_);
	if (ret < 0)
		return ret;

	ret = smsc95xx_read_reg(dev, ID_REV, &read_buf);
	if (ret < 0)
		return ret;
	netif_dbg(dev, ifup, dev->net, "ID_REV = 0x%08x\n", read_buf);

	/* Configure GPIO pins as LED outputs */
	write_buf = LED_GPIO_CFG_SPD_LED | LED_GPIO_CFG_LNK_LED |
		LED_GPIO_CFG_FDX_LED;
	ret = smsc95xx_write_reg(dev, LED_GPIO_CFG, write_buf);
	if (ret < 0)
		return ret;

	/* Init Tx */
	ret = smsc95xx_write_reg(dev, FLOW, 0);
	if (ret < 0)
		return ret;

	ret = smsc95xx_write_reg(dev, AFC_CFG, AFC_CFG_DEFAULT);
	if (ret < 0)
		return ret;

	/* Don't need mac_cr_lock during initialisation */
	ret = smsc95xx_read_reg(dev, MAC_CR, &pdata->mac_cr);
	if (ret < 0)
		return ret;

	/* Init Rx */
	/* Set Vlan */
	ret = smsc95xx_write_reg(dev, VLAN1, (u32)ETH_P_8021Q);
	if (ret < 0)
		return ret;

	/* Enable or disable checksum offload engines */
	ret = smsc95xx_set_features(dev->net, dev->net->features);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to set checksum offload features\n");
		return ret;
	}

	smsc95xx_set_multicast(dev->net);

	ret = smsc95xx_phy_initialize(dev);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to init PHY\n");
		return ret;
	}

	ret = smsc95xx_read_reg(dev, INT_EP_CTL, &read_buf);
	if (ret < 0)
		return ret;

	/* enable PHY interrupts */
	read_buf |= INT_EP_CTL_PHY_INT_;

	ret = smsc95xx_write_reg(dev, INT_EP_CTL, read_buf);
	if (ret < 0)
		return ret;

	ret = smsc95xx_start_tx_path(dev);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to start TX path\n");
		return ret;
	}

	ret = smsc95xx_start_rx_path(dev, 0);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to start RX path\n");
		return ret;
	}

	netif_dbg(dev, ifup, dev->net, "smsc95xx_reset, return 0\n");
	return 0;
}