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
struct mtk_ahci_plat {int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct ahci_host_priv {int /*<<< orphan*/  force_port_map; struct mtk_ahci_plat* plat_data; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_CFG ; 
 int /*<<< orphan*/  SYS_CFG_SATA_EN ; 
 int /*<<< orphan*/  SYS_CFG_SATA_MSK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int mtk_ahci_parse_property(struct ahci_host_priv *hpriv,
				   struct device *dev)
{
	struct mtk_ahci_plat *plat = hpriv->plat_data;
	struct device_node *np = dev->of_node;

	/* enable SATA function if needed */
	if (of_find_property(np, "mediatek,phy-mode", NULL)) {
		plat->mode = syscon_regmap_lookup_by_phandle(
					np, "mediatek,phy-mode");
		if (IS_ERR(plat->mode)) {
			dev_err(dev, "missing phy-mode phandle\n");
			return PTR_ERR(plat->mode);
		}

		regmap_update_bits(plat->mode, SYS_CFG, SYS_CFG_SATA_MSK,
				   SYS_CFG_SATA_EN);
	}

	of_property_read_u32(np, "ports-implemented", &hpriv->force_port_map);

	return 0;
}