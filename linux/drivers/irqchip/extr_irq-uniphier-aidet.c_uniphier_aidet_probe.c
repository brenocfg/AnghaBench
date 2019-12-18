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
struct uniphier_aidet_priv {int /*<<< orphan*/  domain; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg_base; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct irq_domain {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIPHIER_AIDET_NR_IRQS ; 
 struct uniphier_aidet_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_create_hierarchy (struct irq_domain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct uniphier_aidet_priv*) ; 
 struct irq_domain* irq_find_host (struct device_node*) ; 
 struct device_node* of_irq_find_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_aidet_priv*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uniphier_aidet_domain_ops ; 

__attribute__((used)) static int uniphier_aidet_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *parent_np;
	struct irq_domain *parent_domain;
	struct uniphier_aidet_priv *priv;

	parent_np = of_irq_find_parent(dev->of_node);
	if (!parent_np)
		return -ENXIO;

	parent_domain = irq_find_host(parent_np);
	of_node_put(parent_np);
	if (!parent_domain)
		return -EPROBE_DEFER;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->reg_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->reg_base))
		return PTR_ERR(priv->reg_base);

	spin_lock_init(&priv->lock);

	priv->domain = irq_domain_create_hierarchy(
					parent_domain, 0,
					UNIPHIER_AIDET_NR_IRQS,
					of_node_to_fwnode(dev->of_node),
					&uniphier_aidet_domain_ops, priv);
	if (!priv->domain)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	return 0;
}