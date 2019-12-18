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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct usbnet {int rx_urb_size; TYPE_1__* net; scalar_t__ data; } ;
struct ax88179_data {int rxctl; int /*<<< orphan*/  eee_enabled; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/ * AX88179_BULKIN_SIZE ; 
 int AX88179_PHY_ID ; 
 int AX_ACCESS_MAC ; 
 int AX_ACCESS_PHY ; 
 int AX_MEDIUM_EN_125MHZ ; 
 int AX_MEDIUM_FULL_DUPLEX ; 
 int AX_MEDIUM_GIGAMODE ; 
 int AX_MEDIUM_JUMBO_EN ; 
 int AX_MEDIUM_PS ; 
 int AX_MEDIUM_RECEIVE_EN ; 
 int AX_MEDIUM_RXFLOW_CTRLEN ; 
 int /*<<< orphan*/  AX_MEDIUM_STATUS_MODE ; 
 int AX_MEDIUM_TXFLOW_CTRLEN ; 
 int /*<<< orphan*/  AX_RX_BULKIN_QCTRL ; 
 int /*<<< orphan*/  AX_RX_CTL ; 
 int AX_USB_HS ; 
 int AX_USB_SS ; 
 int GMII_PHY_PHYSR ; 
 int GMII_PHY_PHYSR_100 ; 
 int GMII_PHY_PHYSR_FULL ; 
 int GMII_PHY_PHYSR_GIGA ; 
 int GMII_PHY_PHYSR_LINK ; 
 int GMII_PHY_PHYSR_SMASK ; 
 int HZ ; 
 int PHYSICAL_LINK_STATUS ; 
 int /*<<< orphan*/  ax88179_chk_eee (struct usbnet*) ; 
 int /*<<< orphan*/  ax88179_read_cmd (struct usbnet*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  ax88179_write_cmd (struct usbnet*,int,int /*<<< orphan*/ ,int,int,int*) ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_1__*) ; 
 scalar_t__ time_after (int,unsigned long) ; 

__attribute__((used)) static int ax88179_link_reset(struct usbnet *dev)
{
	struct ax88179_data *ax179_data = (struct ax88179_data *)dev->data;
	u8 tmp[5], link_sts;
	u16 mode, tmp16, delay = HZ / 10;
	u32 tmp32 = 0x40000000;
	unsigned long jtimeout;

	jtimeout = jiffies + delay;
	while (tmp32 & 0x40000000) {
		mode = 0;
		ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2, &mode);
		ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_CTL, 2, 2,
				  &ax179_data->rxctl);

		/*link up, check the usb device control TX FIFO full or empty*/
		ax88179_read_cmd(dev, 0x81, 0x8c, 0, 4, &tmp32);

		if (time_after(jiffies, jtimeout))
			return 0;
	}

	mode = AX_MEDIUM_RECEIVE_EN | AX_MEDIUM_TXFLOW_CTRLEN |
	       AX_MEDIUM_RXFLOW_CTRLEN;

	ax88179_read_cmd(dev, AX_ACCESS_MAC, PHYSICAL_LINK_STATUS,
			 1, 1, &link_sts);

	ax88179_read_cmd(dev, AX_ACCESS_PHY, AX88179_PHY_ID,
			 GMII_PHY_PHYSR, 2, &tmp16);

	if (!(tmp16 & GMII_PHY_PHYSR_LINK)) {
		return 0;
	} else if (GMII_PHY_PHYSR_GIGA == (tmp16 & GMII_PHY_PHYSR_SMASK)) {
		mode |= AX_MEDIUM_GIGAMODE | AX_MEDIUM_EN_125MHZ;
		if (dev->net->mtu > 1500)
			mode |= AX_MEDIUM_JUMBO_EN;

		if (link_sts & AX_USB_SS)
			memcpy(tmp, &AX88179_BULKIN_SIZE[0], 5);
		else if (link_sts & AX_USB_HS)
			memcpy(tmp, &AX88179_BULKIN_SIZE[1], 5);
		else
			memcpy(tmp, &AX88179_BULKIN_SIZE[3], 5);
	} else if (GMII_PHY_PHYSR_100 == (tmp16 & GMII_PHY_PHYSR_SMASK)) {
		mode |= AX_MEDIUM_PS;

		if (link_sts & (AX_USB_SS | AX_USB_HS))
			memcpy(tmp, &AX88179_BULKIN_SIZE[2], 5);
		else
			memcpy(tmp, &AX88179_BULKIN_SIZE[3], 5);
	} else {
		memcpy(tmp, &AX88179_BULKIN_SIZE[3], 5);
	}

	/* RX bulk configuration */
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_RX_BULKIN_QCTRL, 5, 5, tmp);

	dev->rx_urb_size = (1024 * (tmp[3] + 2));

	if (tmp16 & GMII_PHY_PHYSR_FULL)
		mode |= AX_MEDIUM_FULL_DUPLEX;
	ax88179_write_cmd(dev, AX_ACCESS_MAC, AX_MEDIUM_STATUS_MODE,
			  2, 2, &mode);

	ax179_data->eee_enabled = ax88179_chk_eee(dev);

	netif_carrier_on(dev->net);

	return 0;
}