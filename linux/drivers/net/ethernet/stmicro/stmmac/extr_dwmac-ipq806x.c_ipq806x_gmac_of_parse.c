#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipq806x_gmac {int id; void* qsgmii_csr; void* nss_common; void* core_clk; scalar_t__ phy_mode; TYPE_1__* pdev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  clk_set_rate (void*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 scalar_t__ of_get_phy_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 void* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ipq806x_gmac_of_parse(struct ipq806x_gmac *gmac)
{
	struct device *dev = &gmac->pdev->dev;

	gmac->phy_mode = of_get_phy_mode(dev->of_node);
	if ((int)gmac->phy_mode < 0) {
		dev_err(dev, "missing phy mode property\n");
		return -EINVAL;
	}

	if (of_property_read_u32(dev->of_node, "qcom,id", &gmac->id) < 0) {
		dev_err(dev, "missing qcom id property\n");
		return -EINVAL;
	}

	/* The GMACs are called 1 to 4 in the documentation, but to simplify the
	 * code and keep it consistent with the Linux convention, we'll number
	 * them from 0 to 3 here.
	 */
	if (gmac->id > 3) {
		dev_err(dev, "invalid gmac id\n");
		return -EINVAL;
	}

	gmac->core_clk = devm_clk_get(dev, "stmmaceth");
	if (IS_ERR(gmac->core_clk)) {
		dev_err(dev, "missing stmmaceth clk property\n");
		return PTR_ERR(gmac->core_clk);
	}
	clk_set_rate(gmac->core_clk, 266000000);

	/* Setup the register map for the nss common registers */
	gmac->nss_common = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "qcom,nss-common");
	if (IS_ERR(gmac->nss_common)) {
		dev_err(dev, "missing nss-common node\n");
		return PTR_ERR(gmac->nss_common);
	}

	/* Setup the register map for the qsgmii csr registers */
	gmac->qsgmii_csr = syscon_regmap_lookup_by_phandle(dev->of_node,
							   "qcom,qsgmii-csr");
	if (IS_ERR(gmac->qsgmii_csr))
		dev_err(dev, "missing qsgmii-csr node\n");

	return PTR_ERR_OR_ZERO(gmac->qsgmii_csr);
}