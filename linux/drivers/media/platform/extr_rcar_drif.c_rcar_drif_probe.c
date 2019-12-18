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
struct rcar_drif_sdr {int /*<<< orphan*/  hw_ch_mask; int /*<<< orphan*/  num_hw_ch; struct rcar_drif** ch; int /*<<< orphan*/ * dev; } ;
struct rcar_drif {int num; struct rcar_drif_sdr* sdr; int /*<<< orphan*/  start; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; struct platform_device* pdev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 void* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hweight_long (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_drif*) ; 
 int rcar_drif_bond_available (struct rcar_drif_sdr*,struct device_node*) ; 
 struct device_node* rcar_drif_bond_enabled (struct platform_device*) ; 
 int /*<<< orphan*/  rcar_drif_primary_bond (struct platform_device*) ; 
 int rcar_drif_sdr_probe (struct rcar_drif_sdr*) ; 

__attribute__((used)) static int rcar_drif_probe(struct platform_device *pdev)
{
	struct rcar_drif_sdr *sdr;
	struct device_node *np;
	struct rcar_drif *ch;
	struct resource	*res;
	int ret;

	/* Reserve memory for enabled channel */
	ch = devm_kzalloc(&pdev->dev, sizeof(*ch), GFP_KERNEL);
	if (!ch)
		return -ENOMEM;

	ch->pdev = pdev;

	/* Module clock */
	ch->clk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(ch->clk)) {
		ret = PTR_ERR(ch->clk);
		dev_err(&pdev->dev, "clk get failed (%d)\n", ret);
		return ret;
	}

	/* Register map */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ch->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ch->base))
		return PTR_ERR(ch->base);

	ch->start = res->start;
	platform_set_drvdata(pdev, ch);

	/* Check if both channels of the bond are enabled */
	np = rcar_drif_bond_enabled(pdev);
	if (np) {
		/* Check if current channel acting as primary-bond */
		if (!rcar_drif_primary_bond(pdev)) {
			ch->num = 1;	/* Primary bond is channel 0 always */
			of_node_put(np);
			return 0;
		}
	}

	/* Reserve memory for SDR structure */
	sdr = devm_kzalloc(&pdev->dev, sizeof(*sdr), GFP_KERNEL);
	if (!sdr) {
		of_node_put(np);
		return -ENOMEM;
	}
	ch->sdr = sdr;
	sdr->dev = &pdev->dev;

	/* Establish links between SDR and channel(s) */
	sdr->ch[ch->num] = ch;
	sdr->hw_ch_mask = BIT(ch->num);
	if (np) {
		/* Check if bonded device is ready */
		ret = rcar_drif_bond_available(sdr, np);
		of_node_put(np);
		if (ret)
			return ret;
	}
	sdr->num_hw_ch = hweight_long(sdr->hw_ch_mask);

	return rcar_drif_sdr_probe(sdr);
}