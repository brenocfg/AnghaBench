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
struct resource {int dummy; } ;
struct mt7621_pcie_port {int slot; int /*<<< orphan*/  list; struct mt7621_pcie* pcie; int /*<<< orphan*/  phy; int /*<<< orphan*/  pcie_rst; int /*<<< orphan*/  base; } ;
struct mt7621_pcie {int /*<<< orphan*/  ports; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mt7621_pcie_port* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int mt7621_pcie_parse_port(struct mt7621_pcie *pcie,
				  struct device_node *node,
				  int slot)
{
	struct mt7621_pcie_port *port;
	struct device *dev = pcie->dev;
	struct device_node *pnode = dev->of_node;
	struct resource regs;
	char name[10];
	int err;

	port = devm_kzalloc(dev, sizeof(*port), GFP_KERNEL);
	if (!port)
		return -ENOMEM;

	err = of_address_to_resource(pnode, slot + 1, &regs);
	if (err) {
		dev_err(dev, "missing \"reg\" property\n");
		return err;
	}

	port->base = devm_ioremap_resource(dev, &regs);
	if (IS_ERR(port->base))
		return PTR_ERR(port->base);

	snprintf(name, sizeof(name), "pcie%d", slot);
	port->pcie_rst = devm_reset_control_get_exclusive(dev, name);
	if (PTR_ERR(port->pcie_rst) == -EPROBE_DEFER) {
		dev_err(dev, "failed to get pcie%d reset control\n", slot);
		return PTR_ERR(port->pcie_rst);
	}

	snprintf(name, sizeof(name), "pcie-phy%d", slot);
	port->phy = devm_phy_get(dev, name);
	if (IS_ERR(port->phy))
		return PTR_ERR(port->phy);

	port->slot = slot;
	port->pcie = pcie;

	INIT_LIST_HEAD(&port->list);
	list_add_tail(&port->list, &pcie->ports);

	return 0;
}