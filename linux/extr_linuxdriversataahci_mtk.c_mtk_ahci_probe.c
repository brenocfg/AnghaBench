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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mtk_ahci_plat {int dummy; } ;
struct ahci_host_priv {struct mtk_ahci_plat* plat_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ahci_host_priv*) ; 
 int PTR_ERR (struct ahci_host_priv*) ; 
 int /*<<< orphan*/  ahci_platform_disable_resources (struct ahci_host_priv*) ; 
 int ahci_platform_enable_resources (struct ahci_host_priv*) ; 
 struct ahci_host_priv* ahci_platform_get_resources (struct platform_device*,int /*<<< orphan*/ ) ; 
 int ahci_platform_init_host (struct platform_device*,struct ahci_host_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahci_platform_sht ; 
 int /*<<< orphan*/  ahci_port_info ; 
 struct mtk_ahci_plat* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int mtk_ahci_parse_property (struct ahci_host_priv*,struct device*) ; 
 int mtk_ahci_platform_resets (struct ahci_host_priv*,struct device*) ; 

__attribute__((used)) static int mtk_ahci_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_ahci_plat *plat;
	struct ahci_host_priv *hpriv;
	int err;

	plat = devm_kzalloc(dev, sizeof(*plat), GFP_KERNEL);
	if (!plat)
		return -ENOMEM;

	hpriv = ahci_platform_get_resources(pdev, 0);
	if (IS_ERR(hpriv))
		return PTR_ERR(hpriv);

	hpriv->plat_data = plat;

	err = mtk_ahci_parse_property(hpriv, dev);
	if (err)
		return err;

	err = mtk_ahci_platform_resets(hpriv, dev);
	if (err)
		return err;

	err = ahci_platform_enable_resources(hpriv);
	if (err)
		return err;

	err = ahci_platform_init_host(pdev, hpriv, &ahci_port_info,
				      &ahci_platform_sht);
	if (err)
		goto disable_resources;

	return 0;

disable_resources:
	ahci_platform_disable_resources(hpriv);
	return err;
}