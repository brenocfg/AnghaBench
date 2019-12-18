#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct b53_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct b53_platform_data {int /*<<< orphan*/  regs; } ;
struct b53_mmap_priv {int /*<<< orphan*/  regs; } ;
struct b53_device {struct b53_platform_data* pdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  b53_mmap_ops ; 
 struct b53_device* b53_switch_alloc (TYPE_1__*,int /*<<< orphan*/ *,struct b53_mmap_priv*) ; 
 int b53_switch_register (struct b53_device*) ; 
 struct b53_mmap_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct b53_device*) ; 

__attribute__((used)) static int b53_mmap_probe(struct platform_device *pdev)
{
	struct b53_platform_data *pdata = pdev->dev.platform_data;
	struct b53_mmap_priv *priv;
	struct b53_device *dev;

	if (!pdata)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->regs = pdata->regs;

	dev = b53_switch_alloc(&pdev->dev, &b53_mmap_ops, priv);
	if (!dev)
		return -ENOMEM;

	dev->pdata = pdata;

	platform_set_drvdata(pdev, dev);

	return b53_switch_register(dev);
}