#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct TYPE_7__ {int active_low; TYPE_3__ rcdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  membase; } ;
struct uniphier_glue_reset_priv {TYPE_4__* clk; TYPE_2__* data; int /*<<< orphan*/ * rst; TYPE_1__ rdata; } ;
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
typedef  int resource_size_t ;
struct TYPE_10__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int nclks; int nrsts; char** reset_names; int /*<<< orphan*/ * clock_names; } ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_CLKS ; 
 int MAX_RSTS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_bulk_disable_unprepare (int,TYPE_4__*) ; 
 int clk_bulk_prepare_enable (int,TYPE_4__*) ; 
 int devm_clk_bulk_get (struct device*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct uniphier_glue_reset_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_shared (struct device*,char const*) ; 
 int devm_reset_controller_register (struct device*,TYPE_3__*) ; 
 TYPE_2__* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_glue_reset_priv*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_simple_ops ; 
 int resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_glue_reset_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uniphier_glue_reset_priv *priv;
	struct resource *res;
	resource_size_t size;
	const char *name;
	int i, ret, nr;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->data = of_device_get_match_data(dev);
	if (WARN_ON(!priv->data || priv->data->nclks > MAX_CLKS ||
		    priv->data->nrsts > MAX_RSTS))
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	size = resource_size(res);
	priv->rdata.membase = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->rdata.membase))
		return PTR_ERR(priv->rdata.membase);

	for (i = 0; i < priv->data->nclks; i++)
		priv->clk[i].id = priv->data->clock_names[i];
	ret = devm_clk_bulk_get(dev, priv->data->nclks, priv->clk);
	if (ret)
		return ret;

	for (i = 0; i < priv->data->nrsts; i++) {
		name = priv->data->reset_names[i];
		priv->rst[i] = devm_reset_control_get_shared(dev, name);
		if (IS_ERR(priv->rst[i]))
			return PTR_ERR(priv->rst[i]);
	}

	ret = clk_bulk_prepare_enable(priv->data->nclks, priv->clk);
	if (ret)
		return ret;

	for (nr = 0; nr < priv->data->nrsts; nr++) {
		ret = reset_control_deassert(priv->rst[nr]);
		if (ret)
			goto out_rst_assert;
	}

	spin_lock_init(&priv->rdata.lock);
	priv->rdata.rcdev.owner = THIS_MODULE;
	priv->rdata.rcdev.nr_resets = size * BITS_PER_BYTE;
	priv->rdata.rcdev.ops = &reset_simple_ops;
	priv->rdata.rcdev.of_node = dev->of_node;
	priv->rdata.active_low = true;

	platform_set_drvdata(pdev, priv);

	ret = devm_reset_controller_register(dev, &priv->rdata.rcdev);
	if (ret)
		goto out_rst_assert;

	return 0;

out_rst_assert:
	while (nr--)
		reset_control_assert(priv->rst[nr]);

	clk_bulk_disable_unprepare(priv->data->nclks, priv->clk);

	return ret;
}