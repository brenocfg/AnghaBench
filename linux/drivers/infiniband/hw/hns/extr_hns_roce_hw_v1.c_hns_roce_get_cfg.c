#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct platform_device {int /*<<< orphan*/  name; } ;
struct of_device_id {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct hns_roce_hw {int dummy; } ;
struct TYPE_8__ {int num_ports; } ;
struct TYPE_7__ {scalar_t__* phy_port; struct net_device** netdevs; } ;
struct TYPE_6__ {int /*<<< orphan*/  node_guid; } ;
struct hns_roce_dev {int cmd_mod; scalar_t__* irq; TYPE_4__* pdev; int /*<<< orphan*/  irq_names; int /*<<< orphan*/  odb_offset; int /*<<< orphan*/  sdb_offset; scalar_t__ loop_idc; TYPE_3__ caps; TYPE_2__ iboe; TYPE_1__ ib_dev; int /*<<< orphan*/  reg_base; struct hns_roce_hw const* hw; } ;
struct fwnode_reference_args {int /*<<< orphan*/  fwnode; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  fwnode; int /*<<< orphan*/  of_node; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_9__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  GUID_LEN ; 
 int HNS_ROCE_MAX_PORTS ; 
 int HNS_ROCE_V1_MAX_IRQ_NUM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ROCEE_DB_OTHERS_L_0_REG ; 
 int /*<<< orphan*/  ROCEE_DB_SQ_L_0_REG ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int acpi_node_get_property_reference (int /*<<< orphan*/ ,char*,int,struct fwnode_reference_args*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ dev_of_node (struct device*) ; 
 int device_property_read_string_array (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int device_property_read_u8_array (struct device*,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_acpi_match ; 
 struct platform_device* hns_roce_find_pdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_roce_of_match ; 
 scalar_t__ is_acpi_device_node (int /*<<< orphan*/ ) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int) ; 
 struct net_device* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ platform_get_irq (TYPE_4__*,int) ; 

__attribute__((used)) static int hns_roce_get_cfg(struct hns_roce_dev *hr_dev)
{
	struct device *dev = &hr_dev->pdev->dev;
	struct platform_device *pdev = NULL;
	struct net_device *netdev = NULL;
	struct device_node *net_node;
	int port_cnt = 0;
	u8 phy_port;
	int ret;
	int i;

	/* check if we are compatible with the underlying SoC */
	if (dev_of_node(dev)) {
		const struct of_device_id *of_id;

		of_id = of_match_node(hns_roce_of_match, dev->of_node);
		if (!of_id) {
			dev_err(dev, "device is not compatible!\n");
			return -ENXIO;
		}
		hr_dev->hw = (const struct hns_roce_hw *)of_id->data;
		if (!hr_dev->hw) {
			dev_err(dev, "couldn't get H/W specific DT data!\n");
			return -ENXIO;
		}
	} else if (is_acpi_device_node(dev->fwnode)) {
		const struct acpi_device_id *acpi_id;

		acpi_id = acpi_match_device(hns_roce_acpi_match, dev);
		if (!acpi_id) {
			dev_err(dev, "device is not compatible!\n");
			return -ENXIO;
		}
		hr_dev->hw = (const struct hns_roce_hw *) acpi_id->driver_data;
		if (!hr_dev->hw) {
			dev_err(dev, "couldn't get H/W specific ACPI data!\n");
			return -ENXIO;
		}
	} else {
		dev_err(dev, "can't read compatibility data from DT or ACPI\n");
		return -ENXIO;
	}

	/* get the mapped register base address */
	hr_dev->reg_base = devm_platform_ioremap_resource(hr_dev->pdev, 0);
	if (IS_ERR(hr_dev->reg_base))
		return PTR_ERR(hr_dev->reg_base);

	/* read the node_guid of IB device from the DT or ACPI */
	ret = device_property_read_u8_array(dev, "node-guid",
					    (u8 *)&hr_dev->ib_dev.node_guid,
					    GUID_LEN);
	if (ret) {
		dev_err(dev, "couldn't get node_guid from DT or ACPI!\n");
		return ret;
	}

	/* get the RoCE associated ethernet ports or netdevices */
	for (i = 0; i < HNS_ROCE_MAX_PORTS; i++) {
		if (dev_of_node(dev)) {
			net_node = of_parse_phandle(dev->of_node, "eth-handle",
						    i);
			if (!net_node)
				continue;
			pdev = of_find_device_by_node(net_node);
		} else if (is_acpi_device_node(dev->fwnode)) {
			struct fwnode_reference_args args;

			ret = acpi_node_get_property_reference(dev->fwnode,
							       "eth-handle",
							       i, &args);
			if (ret)
				continue;
			pdev = hns_roce_find_pdev(args.fwnode);
		} else {
			dev_err(dev, "cannot read data from DT or ACPI\n");
			return -ENXIO;
		}

		if (pdev) {
			netdev = platform_get_drvdata(pdev);
			phy_port = (u8)i;
			if (netdev) {
				hr_dev->iboe.netdevs[port_cnt] = netdev;
				hr_dev->iboe.phy_port[port_cnt] = phy_port;
			} else {
				dev_err(dev, "no netdev found with pdev %s\n",
					pdev->name);
				return -ENODEV;
			}
			port_cnt++;
		}
	}

	if (port_cnt == 0) {
		dev_err(dev, "unable to get eth-handle for available ports!\n");
		return -EINVAL;
	}

	hr_dev->caps.num_ports = port_cnt;

	/* cmd issue mode: 0 is poll, 1 is event */
	hr_dev->cmd_mod = 1;
	hr_dev->loop_idc = 0;
	hr_dev->sdb_offset = ROCEE_DB_SQ_L_0_REG;
	hr_dev->odb_offset = ROCEE_DB_OTHERS_L_0_REG;

	/* read the interrupt names from the DT or ACPI */
	ret = device_property_read_string_array(dev, "interrupt-names",
						hr_dev->irq_names,
						HNS_ROCE_V1_MAX_IRQ_NUM);
	if (ret < 0) {
		dev_err(dev, "couldn't get interrupt names from DT or ACPI!\n");
		return ret;
	}

	/* fetch the interrupt numbers */
	for (i = 0; i < HNS_ROCE_V1_MAX_IRQ_NUM; i++) {
		hr_dev->irq[i] = platform_get_irq(hr_dev->pdev, i);
		if (hr_dev->irq[i] <= 0)
			return -EINVAL;
	}

	return 0;
}