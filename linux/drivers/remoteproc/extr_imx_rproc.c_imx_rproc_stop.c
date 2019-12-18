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
struct rproc {struct imx_rproc* priv; } ;
struct imx_rproc_dcfg {int /*<<< orphan*/  src_stop; int /*<<< orphan*/  src_mask; int /*<<< orphan*/  src_reg; } ;
struct imx_rproc {int /*<<< orphan*/  regmap; struct device* dev; struct imx_rproc_dcfg* dcfg; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx_rproc_stop(struct rproc *rproc)
{
	struct imx_rproc *priv = rproc->priv;
	const struct imx_rproc_dcfg *dcfg = priv->dcfg;
	struct device *dev = priv->dev;
	int ret;

	ret = regmap_update_bits(priv->regmap, dcfg->src_reg,
				 dcfg->src_mask, dcfg->src_stop);
	if (ret)
		dev_err(dev, "Failed to stop M4!\n");

	return ret;
}