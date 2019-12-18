#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct phy_device {TYPE_1__ mdio; int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link; } ;
struct mac_priv_s {int cell_index; int speed; int max_speed; int const* eth_dev; TYPE_2__* fixed_link; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  fman; int /*<<< orphan*/  mc_addr_list; void* internal_phy_node; struct device* dev; } ;
struct mac_device {int phy_if; int if_support; int (* init ) (struct mac_device*) ;int autoneg_pause; int rx_pause_req; int tx_pause_req; int rx_pause_active; int tx_pause_active; int /*<<< orphan*/  addr; struct device_node* phy_node; int /*<<< orphan*/ * port; TYPE_4__* res; struct mac_priv_s* priv; } ;
struct device_node {int dummy; } ;
struct TYPE_7__ {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_6__ {int /*<<< orphan*/  asym_pause; int /*<<< orphan*/  pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int DTSEC_SUPPORTED ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int const*) ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int PHY_INTERFACE_MODE_XGMII ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Half ; 
 TYPE_4__* __devm_request_region (struct device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,struct device_node*) ; 
 int /*<<< orphan*/  devm_ioremap (struct device*,scalar_t__,scalar_t__) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int const* dpaa_eth_add_device (int,struct mac_device*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  fman_bind (struct device*) ; 
 int /*<<< orphan*/  fman_get_mem_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fman_port_bind (struct device*) ; 
 int fman_set_mac_active_pause (struct mac_device*,int,int) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int of_count_phandle_with_args (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 int* of_get_mac_address (struct device_node*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 int of_get_phy_mode (struct device_node*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_parse_phandle (struct device_node*,char*,int) ; 
 struct phy_device* of_phy_find_device (struct device_node*) ; 
 scalar_t__ of_phy_is_fixed_link (struct device_node*) ; 
 int of_phy_register_fixed_link (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 int* phy2speed ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_dtsec (struct mac_device*) ; 
 int /*<<< orphan*/  setup_memac (struct mac_device*) ; 
 int /*<<< orphan*/  setup_tgec (struct mac_device*) ; 
 int stub1 (struct mac_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mac_probe(struct platform_device *_of_dev)
{
	int			 err, i, nph;
	struct device		*dev;
	struct device_node	*mac_node, *dev_node;
	struct mac_device	*mac_dev;
	struct platform_device	*of_dev;
	struct resource		 res;
	struct mac_priv_s	*priv;
	const u8		*mac_addr;
	u32			 val;
	u8			fman_id;
	int			phy_if;

	dev = &_of_dev->dev;
	mac_node = dev->of_node;

	mac_dev = devm_kzalloc(dev, sizeof(*mac_dev), GFP_KERNEL);
	if (!mac_dev) {
		err = -ENOMEM;
		goto _return;
	}
	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv) {
		err = -ENOMEM;
		goto _return;
	}

	/* Save private information */
	mac_dev->priv = priv;
	priv->dev = dev;

	if (of_device_is_compatible(mac_node, "fsl,fman-dtsec")) {
		setup_dtsec(mac_dev);
		priv->internal_phy_node = of_parse_phandle(mac_node,
							  "tbi-handle", 0);
	} else if (of_device_is_compatible(mac_node, "fsl,fman-xgec")) {
		setup_tgec(mac_dev);
	} else if (of_device_is_compatible(mac_node, "fsl,fman-memac")) {
		setup_memac(mac_dev);
		priv->internal_phy_node = of_parse_phandle(mac_node,
							  "pcsphy-handle", 0);
	} else {
		dev_err(dev, "MAC node (%pOF) contains unsupported MAC\n",
			mac_node);
		err = -EINVAL;
		goto _return;
	}

	INIT_LIST_HEAD(&priv->mc_addr_list);

	/* Get the FM node */
	dev_node = of_get_parent(mac_node);
	if (!dev_node) {
		dev_err(dev, "of_get_parent(%pOF) failed\n",
			mac_node);
		err = -EINVAL;
		goto _return_of_get_parent;
	}

	of_dev = of_find_device_by_node(dev_node);
	if (!of_dev) {
		dev_err(dev, "of_find_device_by_node(%pOF) failed\n", dev_node);
		err = -EINVAL;
		goto _return_of_node_put;
	}

	/* Get the FMan cell-index */
	err = of_property_read_u32(dev_node, "cell-index", &val);
	if (err) {
		dev_err(dev, "failed to read cell-index for %pOF\n", dev_node);
		err = -EINVAL;
		goto _return_of_node_put;
	}
	/* cell-index 0 => FMan id 1 */
	fman_id = (u8)(val + 1);

	priv->fman = fman_bind(&of_dev->dev);
	if (!priv->fman) {
		dev_err(dev, "fman_bind(%pOF) failed\n", dev_node);
		err = -ENODEV;
		goto _return_of_node_put;
	}

	of_node_put(dev_node);

	/* Get the address of the memory mapped registers */
	err = of_address_to_resource(mac_node, 0, &res);
	if (err < 0) {
		dev_err(dev, "of_address_to_resource(%pOF) = %d\n",
			mac_node, err);
		goto _return_of_get_parent;
	}

	mac_dev->res = __devm_request_region(dev,
					     fman_get_mem_region(priv->fman),
					     res.start, res.end + 1 - res.start,
					     "mac");
	if (!mac_dev->res) {
		dev_err(dev, "__devm_request_mem_region(mac) failed\n");
		err = -EBUSY;
		goto _return_of_get_parent;
	}

	priv->vaddr = devm_ioremap(dev, mac_dev->res->start,
				   mac_dev->res->end + 1 - mac_dev->res->start);
	if (!priv->vaddr) {
		dev_err(dev, "devm_ioremap() failed\n");
		err = -EIO;
		goto _return_of_get_parent;
	}

	if (!of_device_is_available(mac_node)) {
		err = -ENODEV;
		goto _return_of_get_parent;
	}

	/* Get the cell-index */
	err = of_property_read_u32(mac_node, "cell-index", &val);
	if (err) {
		dev_err(dev, "failed to read cell-index for %pOF\n", mac_node);
		err = -EINVAL;
		goto _return_of_get_parent;
	}
	priv->cell_index = (u8)val;

	/* Get the MAC address */
	mac_addr = of_get_mac_address(mac_node);
	if (IS_ERR(mac_addr)) {
		dev_err(dev, "of_get_mac_address(%pOF) failed\n", mac_node);
		err = -EINVAL;
		goto _return_of_get_parent;
	}
	ether_addr_copy(mac_dev->addr, mac_addr);

	/* Get the port handles */
	nph = of_count_phandle_with_args(mac_node, "fsl,fman-ports", NULL);
	if (unlikely(nph < 0)) {
		dev_err(dev, "of_count_phandle_with_args(%pOF, fsl,fman-ports) failed\n",
			mac_node);
		err = nph;
		goto _return_of_get_parent;
	}

	if (nph != ARRAY_SIZE(mac_dev->port)) {
		dev_err(dev, "Not supported number of fman-ports handles of mac node %pOF from device tree\n",
			mac_node);
		err = -EINVAL;
		goto _return_of_get_parent;
	}

	for (i = 0; i < ARRAY_SIZE(mac_dev->port); i++) {
		/* Find the port node */
		dev_node = of_parse_phandle(mac_node, "fsl,fman-ports", i);
		if (!dev_node) {
			dev_err(dev, "of_parse_phandle(%pOF, fsl,fman-ports) failed\n",
				mac_node);
			err = -EINVAL;
			goto _return_of_node_put;
		}

		of_dev = of_find_device_by_node(dev_node);
		if (!of_dev) {
			dev_err(dev, "of_find_device_by_node(%pOF) failed\n",
				dev_node);
			err = -EINVAL;
			goto _return_of_node_put;
		}

		mac_dev->port[i] = fman_port_bind(&of_dev->dev);
		if (!mac_dev->port[i]) {
			dev_err(dev, "dev_get_drvdata(%pOF) failed\n",
				dev_node);
			err = -EINVAL;
			goto _return_of_node_put;
		}
		of_node_put(dev_node);
	}

	/* Get the PHY connection type */
	phy_if = of_get_phy_mode(mac_node);
	if (phy_if < 0) {
		dev_warn(dev,
			 "of_get_phy_mode() for %pOF failed. Defaulting to SGMII\n",
			 mac_node);
		phy_if = PHY_INTERFACE_MODE_SGMII;
	}
	mac_dev->phy_if = phy_if;

	priv->speed		= phy2speed[mac_dev->phy_if];
	priv->max_speed		= priv->speed;
	mac_dev->if_support	= DTSEC_SUPPORTED;
	/* We don't support half-duplex in SGMII mode */
	if (mac_dev->phy_if == PHY_INTERFACE_MODE_SGMII)
		mac_dev->if_support &= ~(SUPPORTED_10baseT_Half |
					SUPPORTED_100baseT_Half);

	/* Gigabit support (no half-duplex) */
	if (priv->max_speed == 1000)
		mac_dev->if_support |= SUPPORTED_1000baseT_Full;

	/* The 10G interface only supports one mode */
	if (mac_dev->phy_if == PHY_INTERFACE_MODE_XGMII)
		mac_dev->if_support = SUPPORTED_10000baseT_Full;

	/* Get the rest of the PHY information */
	mac_dev->phy_node = of_parse_phandle(mac_node, "phy-handle", 0);
	if (!mac_dev->phy_node && of_phy_is_fixed_link(mac_node)) {
		struct phy_device *phy;

		err = of_phy_register_fixed_link(mac_node);
		if (err)
			goto _return_of_get_parent;

		priv->fixed_link = kzalloc(sizeof(*priv->fixed_link),
					   GFP_KERNEL);
		if (!priv->fixed_link) {
			err = -ENOMEM;
			goto _return_of_get_parent;
		}

		mac_dev->phy_node = of_node_get(mac_node);
		phy = of_phy_find_device(mac_dev->phy_node);
		if (!phy) {
			err = -EINVAL;
			of_node_put(mac_dev->phy_node);
			goto _return_of_get_parent;
		}

		priv->fixed_link->link = phy->link;
		priv->fixed_link->speed = phy->speed;
		priv->fixed_link->duplex = phy->duplex;
		priv->fixed_link->pause = phy->pause;
		priv->fixed_link->asym_pause = phy->asym_pause;

		put_device(&phy->mdio.dev);
	}

	err = mac_dev->init(mac_dev);
	if (err < 0) {
		dev_err(dev, "mac_dev->init() = %d\n", err);
		of_node_put(mac_dev->phy_node);
		goto _return_of_get_parent;
	}

	/* pause frame autonegotiation enabled */
	mac_dev->autoneg_pause = true;

	/* By intializing the values to false, force FMD to enable PAUSE frames
	 * on RX and TX
	 */
	mac_dev->rx_pause_req = true;
	mac_dev->tx_pause_req = true;
	mac_dev->rx_pause_active = false;
	mac_dev->tx_pause_active = false;
	err = fman_set_mac_active_pause(mac_dev, true, true);
	if (err < 0)
		dev_err(dev, "fman_set_mac_active_pause() = %d\n", err);

	dev_info(dev, "FMan MAC address: %pM\n", mac_dev->addr);

	priv->eth_dev = dpaa_eth_add_device(fman_id, mac_dev);
	if (IS_ERR(priv->eth_dev)) {
		dev_err(dev, "failed to add Ethernet platform device for MAC %d\n",
			priv->cell_index);
		priv->eth_dev = NULL;
	}

	goto _return;

_return_of_node_put:
	of_node_put(dev_node);
_return_of_get_parent:
	kfree(priv->fixed_link);
_return:
	return err;
}