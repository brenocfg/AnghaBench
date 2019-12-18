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
struct rtl8xxxu_priv {int chip_cut; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  chip_name; int /*<<< orphan*/  hi_pa; int /*<<< orphan*/  has_gps; int /*<<< orphan*/  has_bluetooth; int /*<<< orphan*/  has_wifi; int /*<<< orphan*/  ep_tx_count; int /*<<< orphan*/  rx_paths; int /*<<< orphan*/  tx_paths; int /*<<< orphan*/  chip_vendor; TYPE_1__* udev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void rtl8xxxu_print_chipinfo(struct rtl8xxxu_priv *priv)
{
	struct device *dev = &priv->udev->dev;
	char *cut;

	switch (priv->chip_cut) {
	case 0:
		cut = "A";
		break;
	case 1:
		cut = "B";
		break;
	case 2:
		cut = "C";
		break;
	case 3:
		cut = "D";
		break;
	case 4:
		cut = "E";
		break;
	default:
		cut = "unknown";
	}

	dev_info(dev,
		 "RTL%s rev %s (%s) %iT%iR, TX queues %i, WiFi=%i, BT=%i, GPS=%i, HI PA=%i\n",
		 priv->chip_name, cut, priv->chip_vendor, priv->tx_paths,
		 priv->rx_paths, priv->ep_tx_count, priv->has_wifi,
		 priv->has_bluetooth, priv->has_gps, priv->hi_pa);

	dev_info(dev, "RTL%s MAC: %pM\n", priv->chip_name, priv->mac_addr);
}