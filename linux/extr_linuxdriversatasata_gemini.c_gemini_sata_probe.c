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
typedef  int u32 ;
struct sata_gemini {int ide_pins; int muxmode; int /*<<< orphan*/  sata0_pclk; int /*<<< orphan*/  sata1_pclk; scalar_t__ sata_bridge; struct regmap* base; struct device* dev; } ;
struct resource {int dummy; } ;
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
typedef  enum gemini_muxmode { ____Placeholder_gemini_muxmode } gemini_muxmode ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GEMINI_GLOBAL_MISC_CTRL ; 
 int GEMINI_IDE_IOMUX_MASK ; 
 int GEMINI_IDE_IOMUX_SHIFT ; 
 int GEMINI_MUXMODE_3 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct regmap* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct sata_gemini* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gemini_sata_bridge_init (struct sata_gemini*) ; 
 int gemini_setup_ide_pins (struct device*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sata_gemini*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 struct sata_gemini* sg_singleton ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int gemini_sata_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct sata_gemini *sg;
	struct regmap *map;
	struct resource *res;
	enum gemini_muxmode muxmode;
	u32 gmode;
	u32 gmask;
	int ret;

	sg = devm_kzalloc(dev, sizeof(*sg), GFP_KERNEL);
	if (!sg)
		return -ENOMEM;
	sg->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	sg->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(sg->base))
		return PTR_ERR(sg->base);

	map = syscon_regmap_lookup_by_phandle(np, "syscon");
	if (IS_ERR(map)) {
		dev_err(dev, "no global syscon\n");
		return PTR_ERR(map);
	}

	/* Set up the SATA bridge if need be */
	if (of_property_read_bool(np, "cortina,gemini-enable-sata-bridge")) {
		ret = gemini_sata_bridge_init(sg);
		if (ret)
			return ret;
	}

	if (of_property_read_bool(np, "cortina,gemini-enable-ide-pins"))
		sg->ide_pins = true;

	if (!sg->sata_bridge && !sg->ide_pins) {
		dev_err(dev, "neither SATA bridge or IDE output enabled\n");
		ret = -EINVAL;
		goto out_unprep_clk;
	}

	ret = of_property_read_u32(np, "cortina,gemini-ata-muxmode", &muxmode);
	if (ret) {
		dev_err(dev, "could not parse ATA muxmode\n");
		goto out_unprep_clk;
	}
	if (muxmode > GEMINI_MUXMODE_3) {
		dev_err(dev, "illegal muxmode %d\n", muxmode);
		ret = -EINVAL;
		goto out_unprep_clk;
	}
	sg->muxmode = muxmode;
	gmask = GEMINI_IDE_IOMUX_MASK;
	gmode = (muxmode << GEMINI_IDE_IOMUX_SHIFT);

	ret = regmap_update_bits(map, GEMINI_GLOBAL_MISC_CTRL, gmask, gmode);
	if (ret) {
		dev_err(dev, "unable to set up IDE muxing\n");
		ret = -ENODEV;
		goto out_unprep_clk;
	}

	/*
	 * Route out the IDE pins if desired.
	 * This is done by looking up a special pin control state called
	 * "ide" that will route out the IDE pins.
	 */
	if (sg->ide_pins) {
		ret = gemini_setup_ide_pins(dev);
		if (ret)
			return ret;
	}

	dev_info(dev, "set up the Gemini IDE/SATA nexus\n");
	platform_set_drvdata(pdev, sg);
	sg_singleton = sg;

	return 0;

out_unprep_clk:
	if (sg->sata_bridge) {
		clk_unprepare(sg->sata1_pclk);
		clk_unprepare(sg->sata0_pclk);
	}
	return ret;
}