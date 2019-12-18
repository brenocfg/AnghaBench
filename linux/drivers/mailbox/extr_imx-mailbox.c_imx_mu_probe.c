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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_4__ {unsigned int num_chans; int txdone_irq; int /*<<< orphan*/  of_xlate; TYPE_1__* chans; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct imx_mu_priv {scalar_t__ irq; TYPE_2__ mbox; TYPE_1__* mbox_chans; int /*<<< orphan*/  xcr_lock; int /*<<< orphan*/  side_b; struct imx_mu_con_priv* con_priv; int /*<<< orphan*/ * clk; int /*<<< orphan*/ * base; struct device* dev; } ;
struct imx_mu_con_priv {unsigned int idx; unsigned int type; int /*<<< orphan*/  irq_desc; TYPE_1__* chan; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct imx_mu_con_priv* con_priv; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int IMX_MU_CHANS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct imx_mu_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mbox_controller_register (struct device*,TYPE_2__*) ; 
 int /*<<< orphan*/ * devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_mu_init_generic (struct imx_mu_priv*) ; 
 int /*<<< orphan*/  imx_mu_ops ; 
 int /*<<< orphan*/  imx_mu_xlate ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_mu_priv*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx_mu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct imx_mu_priv *priv;
	unsigned int i;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;

	priv->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->irq = platform_get_irq(pdev, 0);
	if (priv->irq < 0)
		return priv->irq;

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk)) {
		if (PTR_ERR(priv->clk) != -ENOENT)
			return PTR_ERR(priv->clk);

		priv->clk = NULL;
	}

	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(dev, "Failed to enable clock\n");
		return ret;
	}

	for (i = 0; i < IMX_MU_CHANS; i++) {
		struct imx_mu_con_priv *cp = &priv->con_priv[i];

		cp->idx = i % 4;
		cp->type = i >> 2;
		cp->chan = &priv->mbox_chans[i];
		priv->mbox_chans[i].con_priv = cp;
		snprintf(cp->irq_desc, sizeof(cp->irq_desc),
			 "imx_mu_chan[%i-%i]", cp->type, cp->idx);
	}

	priv->side_b = of_property_read_bool(np, "fsl,mu-side-b");

	spin_lock_init(&priv->xcr_lock);

	priv->mbox.dev = dev;
	priv->mbox.ops = &imx_mu_ops;
	priv->mbox.chans = priv->mbox_chans;
	priv->mbox.num_chans = IMX_MU_CHANS;
	priv->mbox.of_xlate = imx_mu_xlate;
	priv->mbox.txdone_irq = true;

	platform_set_drvdata(pdev, priv);

	imx_mu_init_generic(priv);

	return devm_mbox_controller_register(dev, &priv->mbox);
}