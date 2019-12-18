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
struct regmap {int dummy; } ;
struct dw_mci_zx_priv_data {struct regmap* sysc_base; } ;
struct dw_mci {struct dw_mci_zx_priv_data* priv; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_3__ {struct device_node* of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct dw_mci_zx_priv_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int dw_mci_zx_parse_dt(struct dw_mci *host)
{
	struct device_node *np = host->dev->of_node;
	struct device_node *node;
	struct dw_mci_zx_priv_data *priv;
	struct regmap *sysc_base;
	int ret;

	/* syscon is needed only by emmc */
	node = of_parse_phandle(np, "zte,aon-syscon", 0);
	if (node) {
		sysc_base = syscon_node_to_regmap(node);
		of_node_put(node);

		if (IS_ERR(sysc_base)) {
			ret = PTR_ERR(sysc_base);
			if (ret != -EPROBE_DEFER)
				dev_err(host->dev, "Can't get syscon: %d\n",
					ret);
			return ret;
		}
	} else {
		return 0;
	}

	priv = devm_kzalloc(host->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->sysc_base = sysc_base;
	host->priv = priv;

	return 0;
}