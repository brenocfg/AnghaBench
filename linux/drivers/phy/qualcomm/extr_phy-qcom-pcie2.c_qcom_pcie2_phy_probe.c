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
struct resource {int dummy; } ;
struct qcom_phy {struct phy_provider* pipe_reset; struct phy_provider* phy_reset; struct phy_provider* pipe_clk; TYPE_1__* vregs; struct phy_provider* base; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider phy ;
struct TYPE_3__ {char* supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct phy_provider* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qcom_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int phy_pipe_clksrc_register (struct qcom_phy*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct qcom_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qcom_pcie2_ops ; 

__attribute__((used)) static int qcom_pcie2_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct qcom_phy *qphy;
	struct resource *res;
	struct device *dev = &pdev->dev;
	struct phy *phy;
	int ret;

	qphy = devm_kzalloc(dev, sizeof(*qphy), GFP_KERNEL);
	if (!qphy)
		return -ENOMEM;

	qphy->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	qphy->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(qphy->base))
		return PTR_ERR(qphy->base);

	ret = phy_pipe_clksrc_register(qphy);
	if (ret) {
		dev_err(dev, "failed to register pipe_clk\n");
		return ret;
	}

	qphy->vregs[0].supply = "vdda-vp";
	qphy->vregs[1].supply = "vdda-vph";
	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(qphy->vregs), qphy->vregs);
	if (ret < 0)
		return ret;

	qphy->pipe_clk = devm_clk_get(dev, NULL);
	if (IS_ERR(qphy->pipe_clk)) {
		dev_err(dev, "failed to acquire pipe clock\n");
		return PTR_ERR(qphy->pipe_clk);
	}

	qphy->phy_reset = devm_reset_control_get_exclusive(dev, "phy");
	if (IS_ERR(qphy->phy_reset)) {
		dev_err(dev, "failed to acquire phy reset\n");
		return PTR_ERR(qphy->phy_reset);
	}

	qphy->pipe_reset = devm_reset_control_get_exclusive(dev, "pipe");
	if (IS_ERR(qphy->pipe_reset)) {
		dev_err(dev, "failed to acquire pipe reset\n");
		return PTR_ERR(qphy->pipe_reset);
	}

	phy = devm_phy_create(dev, dev->of_node, &qcom_pcie2_ops);
	if (IS_ERR(phy)) {
		dev_err(dev, "failed to create phy\n");
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, qphy);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (IS_ERR(phy_provider))
		dev_err(dev, "failed to register phy provider\n");

	return PTR_ERR_OR_ZERO(phy_provider);
}