#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {int nr_resets; int of_reset_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/  of_node; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct lantiq_rcu_reset_priv {TYPE_1__ rcdev; TYPE_2__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct lantiq_rcu_reset_priv* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int lantiq_rcu_reset_of_parse (struct platform_device*,struct lantiq_rcu_reset_priv*) ; 
 int /*<<< orphan*/  lantiq_rcu_reset_ops ; 
 int /*<<< orphan*/  lantiq_rcu_reset_xlate ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lantiq_rcu_reset_priv*) ; 
 int reset_controller_register (TYPE_1__*) ; 

__attribute__((used)) static int lantiq_rcu_reset_probe(struct platform_device *pdev)
{
	struct lantiq_rcu_reset_priv *priv;
	int err;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = &pdev->dev;
	platform_set_drvdata(pdev, priv);

	err = lantiq_rcu_reset_of_parse(pdev, priv);
	if (err)
		return err;

	priv->rcdev.ops = &lantiq_rcu_reset_ops;
	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.of_node = pdev->dev.of_node;
	priv->rcdev.nr_resets = 32;
	priv->rcdev.of_xlate = lantiq_rcu_reset_xlate;
	priv->rcdev.of_reset_n_cells = 2;

	return reset_controller_register(&priv->rcdev);
}