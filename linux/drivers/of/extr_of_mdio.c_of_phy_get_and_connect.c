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
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct device_node {int dummy; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 scalar_t__ of_get_phy_mode (struct device_node*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct phy_device* of_phy_connect (struct net_device*,struct device_node*,void (*) (struct net_device*),int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 

struct phy_device *of_phy_get_and_connect(struct net_device *dev,
					  struct device_node *np,
					  void (*hndlr)(struct net_device *))
{
	phy_interface_t iface;
	struct device_node *phy_np;
	struct phy_device *phy;
	int ret;

	iface = of_get_phy_mode(np);
	if ((int)iface < 0)
		return NULL;
	if (of_phy_is_fixed_link(np)) {
		ret = of_phy_register_fixed_link(np);
		if (ret < 0) {
			netdev_err(dev, "broken fixed-link specification\n");
			return NULL;
		}
		phy_np = of_node_get(np);
	} else {
		phy_np = of_parse_phandle(np, "phy-handle", 0);
		if (!phy_np)
			return NULL;
	}

	phy = of_phy_connect(dev, phy_np, hndlr, 0, iface);

	of_node_put(phy_np);

	return phy;
}