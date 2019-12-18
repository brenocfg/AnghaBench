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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct m48t35_priv {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  size; int /*<<< orphan*/  baseaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct m48t35_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m48t35_ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct m48t35_priv*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int m48t35_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct m48t35_priv *priv;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;
	priv = devm_kzalloc(&pdev->dev, sizeof(struct m48t35_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->size = resource_size(res);
	/*
	 * kludge: remove the #ifndef after ioc3 resource
	 * conflicts are resolved
	 */
#ifndef CONFIG_SGI_IP27
	if (!devm_request_mem_region(&pdev->dev, res->start, priv->size,
				     pdev->name))
		return -EBUSY;
#endif
	priv->baseaddr = res->start;
	priv->reg = devm_ioremap(&pdev->dev, priv->baseaddr, priv->size);
	if (!priv->reg)
		return -ENOMEM;

	spin_lock_init(&priv->lock);

	platform_set_drvdata(pdev, priv);

	priv->rtc = devm_rtc_device_register(&pdev->dev, "m48t35",
				  &m48t35_ops, THIS_MODULE);
	return PTR_ERR_OR_ZERO(priv->rtc);
}