#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sja1105_xmii_params_entry {int /*<<< orphan*/ * phy_mac; int /*<<< orphan*/ * xmii_mode; } ;
struct sja1105_table {struct sja1105_xmii_params_entry* entries; scalar_t__ entry_count; TYPE_3__* ops; } ;
struct TYPE_5__ {struct sja1105_table* tables; } ;
struct sja1105_private {TYPE_2__ static_config; TYPE_1__* spidev; } ;
struct sja1105_dt_port {int phy_mode; int /*<<< orphan*/  role; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  unpacked_entry_size; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 size_t BLK_IDX_XMII_PARAMS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 scalar_t__ SJA1105_MAX_XMII_PARAMS_COUNT ; 
 int SJA1105_NUM_PORTS ; 
 int /*<<< orphan*/  XMII_MODE_MII ; 
 int /*<<< orphan*/  XMII_MODE_RGMII ; 
 int /*<<< orphan*/  XMII_MODE_RMII ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct sja1105_xmii_params_entry* kcalloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sja1105_xmii_params_entry*) ; 
 int /*<<< orphan*/  phy_modes (int) ; 

__attribute__((used)) static int sja1105_init_mii_settings(struct sja1105_private *priv,
				     struct sja1105_dt_port *ports)
{
	struct device *dev = &priv->spidev->dev;
	struct sja1105_xmii_params_entry *mii;
	struct sja1105_table *table;
	int i;

	table = &priv->static_config.tables[BLK_IDX_XMII_PARAMS];

	/* Discard previous xMII Mode Parameters Table */
	if (table->entry_count) {
		kfree(table->entries);
		table->entry_count = 0;
	}

	table->entries = kcalloc(SJA1105_MAX_XMII_PARAMS_COUNT,
				 table->ops->unpacked_entry_size, GFP_KERNEL);
	if (!table->entries)
		return -ENOMEM;

	/* Override table based on PHYLINK DT bindings */
	table->entry_count = SJA1105_MAX_XMII_PARAMS_COUNT;

	mii = table->entries;

	for (i = 0; i < SJA1105_NUM_PORTS; i++) {
		switch (ports[i].phy_mode) {
		case PHY_INTERFACE_MODE_MII:
			mii->xmii_mode[i] = XMII_MODE_MII;
			break;
		case PHY_INTERFACE_MODE_RMII:
			mii->xmii_mode[i] = XMII_MODE_RMII;
			break;
		case PHY_INTERFACE_MODE_RGMII:
		case PHY_INTERFACE_MODE_RGMII_ID:
		case PHY_INTERFACE_MODE_RGMII_RXID:
		case PHY_INTERFACE_MODE_RGMII_TXID:
			mii->xmii_mode[i] = XMII_MODE_RGMII;
			break;
		default:
			dev_err(dev, "Unsupported PHY mode %s!\n",
				phy_modes(ports[i].phy_mode));
		}

		mii->phy_mac[i] = ports[i].role;
	}
	return 0;
}