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
struct device {struct device* parent; struct device_node* of_node; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {TYPE_1__ mdio; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ9031RN_CLK_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_CONTROL_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_RX_DATA_PAD_SKEW ; 
 int /*<<< orphan*/  MII_KSZ9031RN_TX_DATA_PAD_SKEW ; 
 int ksz9131_of_load_skew_values (struct phy_device*,struct device_node*,int /*<<< orphan*/ ,int,char**,int) ; 

__attribute__((used)) static int ksz9131_config_init(struct phy_device *phydev)
{
	const struct device *dev = &phydev->mdio.dev;
	struct device_node *of_node = dev->of_node;
	char *clk_skews[2] = {"rxc-skew-psec", "txc-skew-psec"};
	char *rx_data_skews[4] = {
		"rxd0-skew-psec", "rxd1-skew-psec",
		"rxd2-skew-psec", "rxd3-skew-psec"
	};
	char *tx_data_skews[4] = {
		"txd0-skew-psec", "txd1-skew-psec",
		"txd2-skew-psec", "txd3-skew-psec"
	};
	char *control_skews[2] = {"txen-skew-psec", "rxdv-skew-psec"};
	const struct device *dev_walker;
	int ret;

	dev_walker = &phydev->mdio.dev;
	do {
		of_node = dev_walker->of_node;
		dev_walker = dev_walker->parent;
	} while (!of_node && dev_walker);

	if (!of_node)
		return 0;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_CLK_PAD_SKEW, 5,
					  clk_skews, 2);
	if (ret < 0)
		return ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_CONTROL_PAD_SKEW, 4,
					  control_skews, 2);
	if (ret < 0)
		return ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_RX_DATA_PAD_SKEW, 4,
					  rx_data_skews, 4);
	if (ret < 0)
		return ret;

	ret = ksz9131_of_load_skew_values(phydev, of_node,
					  MII_KSZ9031RN_TX_DATA_PAD_SKEW, 4,
					  tx_data_skews, 4);
	if (ret < 0)
		return ret;

	return 0;
}