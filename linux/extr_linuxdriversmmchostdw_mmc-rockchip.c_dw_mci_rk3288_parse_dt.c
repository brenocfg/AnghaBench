#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dw_mci_rockchip_priv_data {int num_phases; int default_sample_phase; void* sample_clk; void* drv_clk; } ;
struct dw_mci {struct dw_mci_rockchip_priv_data* priv; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct dw_mci_rockchip_priv_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int dw_mci_rk3288_parse_dt(struct dw_mci *host)
{
	struct device_node *np = host->dev->of_node;
	struct dw_mci_rockchip_priv_data *priv;

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	if (of_property_read_u32(np, "rockchip,desired-num-phases",
					&priv->num_phases))
		priv->num_phases = 360;

	if (of_property_read_u32(np, "rockchip,default-sample-phase",
					&priv->default_sample_phase))
		priv->default_sample_phase = 0;

	priv->drv_clk = devm_clk_get(host->dev, "ciu-drive");
	if (IS_ERR(priv->drv_clk))
		dev_dbg(host->dev, "ciu-drive not available\n");

	priv->sample_clk = devm_clk_get(host->dev, "ciu-sample");
	if (IS_ERR(priv->sample_clk))
		dev_dbg(host->dev, "ciu-sample not available\n");

	host->priv = priv;

	return 0;
}