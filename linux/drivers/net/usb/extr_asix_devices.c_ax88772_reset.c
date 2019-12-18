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
struct usbnet {TYPE_1__* net; int /*<<< orphan*/  data; } ;
struct asix_data {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX88772_MEDIUM_DEFAULT ; 
 int /*<<< orphan*/  AX_CMD_WRITE_NODE_ID ; 
 int /*<<< orphan*/  AX_DEFAULT_RX_CTL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int asix_write_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asix_write_medium_mode (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int asix_write_rx_ctl (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ax88772_reset(struct usbnet *dev)
{
	struct asix_data *data = (struct asix_data *)&dev->data;
	int ret;

	/* Rewrite MAC address */
	ether_addr_copy(data->mac_addr, dev->net->dev_addr);
	ret = asix_write_cmd(dev, AX_CMD_WRITE_NODE_ID, 0, 0,
			     ETH_ALEN, data->mac_addr, 0);
	if (ret < 0)
		goto out;

	/* Set RX_CTL to default values with 2k buffer, and enable cactus */
	ret = asix_write_rx_ctl(dev, AX_DEFAULT_RX_CTL, 0);
	if (ret < 0)
		goto out;

	ret = asix_write_medium_mode(dev, AX88772_MEDIUM_DEFAULT, 0);
	if (ret < 0)
		goto out;

	return 0;

out:
	return ret;
}