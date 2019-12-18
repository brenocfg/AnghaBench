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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct bcmgenet_priv {struct device_node* mdio_dn; int /*<<< orphan*/  version; TYPE_1__* pdev; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct device_node* of_get_compatible_child (struct device_node*,char*) ; 

__attribute__((used)) static struct device_node *bcmgenet_mii_of_find_mdio(struct bcmgenet_priv *priv)
{
	struct device_node *dn = priv->pdev->dev.of_node;
	struct device *kdev = &priv->pdev->dev;
	char *compat;

	compat = kasprintf(GFP_KERNEL, "brcm,genet-mdio-v%d", priv->version);
	if (!compat)
		return NULL;

	priv->mdio_dn = of_get_compatible_child(dn, compat);
	kfree(compat);
	if (!priv->mdio_dn) {
		dev_err(kdev, "unable to find MDIO bus node\n");
		return NULL;
	}

	return priv->mdio_dn;
}