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
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct resource {int dummy; } ;
struct qusb2_phy {int override_imp_res_offset; int override_hstx_trim; int override_preemphasis; int override_preemphasis_width; struct phy_provider* phy; void* preemphasis_width; void* preemphasis_level; void* hstx_trim_value; void* imp_res_offset_value; struct phy_provider* cell; struct phy_provider* tcsr; int /*<<< orphan*/  cfg; TYPE_1__* vregs; struct phy_provider* phy_reset; struct phy_provider* iface_clk; struct phy_provider* ref_clk; struct phy_provider* cfg_ahb_clk; struct phy_provider* base; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider phy ;
struct TYPE_3__ {int /*<<< orphan*/  supply; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct qusb2_phy*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 struct phy_provider* devm_clk_get_optional (struct device*,char*) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct qusb2_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_nvmem_cell_get (struct device*,int /*<<< orphan*/ *) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 struct phy_provider* devm_reset_control_get_by_index (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct qusb2_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_forbid (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  qusb2_phy_gen_ops ; 
 int /*<<< orphan*/ * qusb2_phy_vreg_names ; 
 struct phy_provider* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int qusb2_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct qusb2_phy *qphy;
	struct phy_provider *phy_provider;
	struct phy *generic_phy;
	struct resource *res;
	int ret, i;
	int num;
	u32 value;

	qphy = devm_kzalloc(dev, sizeof(*qphy), GFP_KERNEL);
	if (!qphy)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	qphy->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(qphy->base))
		return PTR_ERR(qphy->base);

	qphy->cfg_ahb_clk = devm_clk_get(dev, "cfg_ahb");
	if (IS_ERR(qphy->cfg_ahb_clk)) {
		ret = PTR_ERR(qphy->cfg_ahb_clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get cfg ahb clk, %d\n", ret);
		return ret;
	}

	qphy->ref_clk = devm_clk_get(dev, "ref");
	if (IS_ERR(qphy->ref_clk)) {
		ret = PTR_ERR(qphy->ref_clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get ref clk, %d\n", ret);
		return ret;
	}

	qphy->iface_clk = devm_clk_get_optional(dev, "iface");
	if (IS_ERR(qphy->iface_clk))
		return PTR_ERR(qphy->iface_clk);

	qphy->phy_reset = devm_reset_control_get_by_index(&pdev->dev, 0);
	if (IS_ERR(qphy->phy_reset)) {
		dev_err(dev, "failed to get phy core reset\n");
		return PTR_ERR(qphy->phy_reset);
	}

	num = ARRAY_SIZE(qphy->vregs);
	for (i = 0; i < num; i++)
		qphy->vregs[i].supply = qusb2_phy_vreg_names[i];

	ret = devm_regulator_bulk_get(dev, num, qphy->vregs);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to get regulator supplies: %d\n",
				ret);
		return ret;
	}

	/* Get the specific init parameters of QMP phy */
	qphy->cfg = of_device_get_match_data(dev);

	qphy->tcsr = syscon_regmap_lookup_by_phandle(dev->of_node,
							"qcom,tcsr-syscon");
	if (IS_ERR(qphy->tcsr)) {
		dev_dbg(dev, "failed to lookup TCSR regmap\n");
		qphy->tcsr = NULL;
	}

	qphy->cell = devm_nvmem_cell_get(dev, NULL);
	if (IS_ERR(qphy->cell)) {
		if (PTR_ERR(qphy->cell) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		qphy->cell = NULL;
		dev_dbg(dev, "failed to lookup tune2 hstx trim value\n");
	}

	if (!of_property_read_u32(dev->of_node, "qcom,imp-res-offset-value",
				  &value)) {
		qphy->imp_res_offset_value = (u8)value;
		qphy->override_imp_res_offset = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,hstx-trim-value",
				  &value)) {
		qphy->hstx_trim_value = (u8)value;
		qphy->override_hstx_trim = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,preemphasis-level",
				     &value)) {
		qphy->preemphasis_level = (u8)value;
		qphy->override_preemphasis = true;
	}

	if (!of_property_read_u32(dev->of_node, "qcom,preemphasis-width",
				     &value)) {
		qphy->preemphasis_width = (u8)value;
		qphy->override_preemphasis_width = true;
	}

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	/*
	 * Prevent runtime pm from being ON by default. Users can enable
	 * it using power/control in sysfs.
	 */
	pm_runtime_forbid(dev);

	generic_phy = devm_phy_create(dev, NULL, &qusb2_phy_gen_ops);
	if (IS_ERR(generic_phy)) {
		ret = PTR_ERR(generic_phy);
		dev_err(dev, "failed to create phy, %d\n", ret);
		pm_runtime_disable(dev);
		return ret;
	}
	qphy->phy = generic_phy;

	dev_set_drvdata(dev, qphy);
	phy_set_drvdata(generic_phy, qphy);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (!IS_ERR(phy_provider))
		dev_info(dev, "Registered Qcom-QUSB2 phy\n");
	else
		pm_runtime_disable(dev);

	return PTR_ERR_OR_ZERO(phy_provider);
}