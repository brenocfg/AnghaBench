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
struct serdes_am654 {void* pll_ok; void* pll_enable; void* rx0_enable; void* tx0_enable; void* por_en; void* cmu_ok_i_0; void* l1_master_cdn_o; void* config_version; void* cmu_master_cdn_o; struct device* dev; struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  cmu_master_cdn_o ; 
 int /*<<< orphan*/  cmu_ok_i_0 ; 
 int /*<<< orphan*/  config_version ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_regmap_field_alloc (struct device*,struct regmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l1_master_cdn_o ; 
 int /*<<< orphan*/  pll_enable ; 
 int /*<<< orphan*/  pll_ok ; 
 int /*<<< orphan*/  por_en ; 
 int /*<<< orphan*/  rx0_enable ; 
 int /*<<< orphan*/  tx0_enable ; 

__attribute__((used)) static int serdes_am654_regfield_init(struct serdes_am654 *am654_phy)
{
	struct regmap *regmap = am654_phy->regmap;
	struct device *dev = am654_phy->dev;

	am654_phy->cmu_master_cdn_o = devm_regmap_field_alloc(dev, regmap,
							      cmu_master_cdn_o);
	if (IS_ERR(am654_phy->cmu_master_cdn_o)) {
		dev_err(dev, "CMU_MASTER_CDN_O reg field init failed\n");
		return PTR_ERR(am654_phy->cmu_master_cdn_o);
	}

	am654_phy->config_version = devm_regmap_field_alloc(dev, regmap,
							    config_version);
	if (IS_ERR(am654_phy->config_version)) {
		dev_err(dev, "CONFIG_VERSION reg field init failed\n");
		return PTR_ERR(am654_phy->config_version);
	}

	am654_phy->l1_master_cdn_o = devm_regmap_field_alloc(dev, regmap,
							     l1_master_cdn_o);
	if (IS_ERR(am654_phy->l1_master_cdn_o)) {
		dev_err(dev, "L1_MASTER_CDN_O reg field init failed\n");
		return PTR_ERR(am654_phy->l1_master_cdn_o);
	}

	am654_phy->cmu_ok_i_0 = devm_regmap_field_alloc(dev, regmap,
							cmu_ok_i_0);
	if (IS_ERR(am654_phy->cmu_ok_i_0)) {
		dev_err(dev, "CMU_OK_I_0 reg field init failed\n");
		return PTR_ERR(am654_phy->cmu_ok_i_0);
	}

	am654_phy->por_en = devm_regmap_field_alloc(dev, regmap, por_en);
	if (IS_ERR(am654_phy->por_en)) {
		dev_err(dev, "POR_EN reg field init failed\n");
		return PTR_ERR(am654_phy->por_en);
	}

	am654_phy->tx0_enable = devm_regmap_field_alloc(dev, regmap,
							tx0_enable);
	if (IS_ERR(am654_phy->tx0_enable)) {
		dev_err(dev, "TX0_ENABLE reg field init failed\n");
		return PTR_ERR(am654_phy->tx0_enable);
	}

	am654_phy->rx0_enable = devm_regmap_field_alloc(dev, regmap,
							rx0_enable);
	if (IS_ERR(am654_phy->rx0_enable)) {
		dev_err(dev, "RX0_ENABLE reg field init failed\n");
		return PTR_ERR(am654_phy->rx0_enable);
	}

	am654_phy->pll_enable = devm_regmap_field_alloc(dev, regmap,
							pll_enable);
	if (IS_ERR(am654_phy->pll_enable)) {
		dev_err(dev, "PLL_ENABLE reg field init failed\n");
		return PTR_ERR(am654_phy->pll_enable);
	}

	am654_phy->pll_ok = devm_regmap_field_alloc(dev, regmap, pll_ok);
	if (IS_ERR(am654_phy->pll_ok)) {
		dev_err(dev, "PLL_OK reg field init failed\n");
		return PTR_ERR(am654_phy->pll_ok);
	}

	return 0;
}