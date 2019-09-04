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
struct unimac_mdio_pdata {char* bus_name; int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; struct bcmgenet_priv* wait_func_data; int /*<<< orphan*/  wait_func; } ;
struct resource {char* bus_name; int /*<<< orphan*/  flags; scalar_t__ start; scalar_t__ end; struct bcmgenet_priv* wait_func_data; int /*<<< orphan*/  wait_func; } ;
struct TYPE_2__ {struct device_node* of_node; struct TYPE_2__* parent; struct bcmgenet_platform_data* platform_data; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct bcmgenet_priv {struct platform_device* mii_pdev; struct platform_device* pdev; } ;
struct bcmgenet_platform_data {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  ppd ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ GENET_UMAC_OFF ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ UMAC_MDIO_CMD ; 
 int /*<<< orphan*/  UNIMAC_MDIO_DRV_NAME ; 
 struct device_node* bcmgenet_mii_of_find_mdio (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_mii_pdata_init (struct bcmgenet_priv*,struct unimac_mdio_pdata*) ; 
 int /*<<< orphan*/  bcmgenet_mii_wait ; 
 int /*<<< orphan*/  memset (struct unimac_mdio_pdata*,int /*<<< orphan*/ ,int) ; 
 int of_alias_get_id (struct device_node*,char*) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct unimac_mdio_pdata*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct unimac_mdio_pdata*,int) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 struct unimac_mdio_pdata* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcmgenet_mii_register(struct bcmgenet_priv *priv)
{
	struct platform_device *pdev = priv->pdev;
	struct bcmgenet_platform_data *pdata = pdev->dev.platform_data;
	struct device_node *dn = pdev->dev.of_node;
	struct unimac_mdio_pdata ppd;
	struct platform_device *ppdev;
	struct resource *pres, res;
	int id, ret;

	pres = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	memset(&res, 0, sizeof(res));
	memset(&ppd, 0, sizeof(ppd));

	ppd.wait_func = bcmgenet_mii_wait;
	ppd.wait_func_data = priv;
	ppd.bus_name = "bcmgenet MII bus";

	/* Unimac MDIO bus controller starts at UniMAC offset + MDIO_CMD
	 * and is 2 * 32-bits word long, 8 bytes total.
	 */
	res.start = pres->start + GENET_UMAC_OFF + UMAC_MDIO_CMD;
	res.end = res.start + 8;
	res.flags = IORESOURCE_MEM;

	if (dn)
		id = of_alias_get_id(dn, "eth");
	else
		id = pdev->id;

	ppdev = platform_device_alloc(UNIMAC_MDIO_DRV_NAME, id);
	if (!ppdev)
		return -ENOMEM;

	/* Retain this platform_device pointer for later cleanup */
	priv->mii_pdev = ppdev;
	ppdev->dev.parent = &pdev->dev;
	ppdev->dev.of_node = bcmgenet_mii_of_find_mdio(priv);
	if (pdata)
		bcmgenet_mii_pdata_init(priv, &ppd);

	ret = platform_device_add_resources(ppdev, &res, 1);
	if (ret)
		goto out;

	ret = platform_device_add_data(ppdev, &ppd, sizeof(ppd));
	if (ret)
		goto out;

	ret = platform_device_add(ppdev);
	if (ret)
		goto out;

	return 0;
out:
	platform_device_put(ppdev);
	return ret;
}