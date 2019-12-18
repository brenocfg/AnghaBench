#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct ulpi {TYPE_1__ dev; } ;
struct qcom_usb_hsic_phy {struct clk* phy; struct clk* cal_sleep_clk; struct clk* cal_clk; struct clk* phy_clk; struct clk* pctl; struct ulpi* ulpi; } ;
struct phy_provider {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 struct clk* devm_clk_get (TYPE_1__*,char*) ; 
 struct qcom_usb_hsic_phy* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct clk* devm_phy_create (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk* devm_pinctrl_get (TYPE_1__*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct clk*,struct qcom_usb_hsic_phy*) ; 
 int /*<<< orphan*/  qcom_usb_hsic_phy_ops ; 
 int /*<<< orphan*/  ulpi_set_drvdata (struct ulpi*,struct qcom_usb_hsic_phy*) ; 

__attribute__((used)) static int qcom_usb_hsic_phy_probe(struct ulpi *ulpi)
{
	struct qcom_usb_hsic_phy *uphy;
	struct phy_provider *p;
	struct clk *clk;

	uphy = devm_kzalloc(&ulpi->dev, sizeof(*uphy), GFP_KERNEL);
	if (!uphy)
		return -ENOMEM;
	ulpi_set_drvdata(ulpi, uphy);

	uphy->ulpi = ulpi;
	uphy->pctl = devm_pinctrl_get(&ulpi->dev);
	if (IS_ERR(uphy->pctl))
		return PTR_ERR(uphy->pctl);

	uphy->phy_clk = clk = devm_clk_get(&ulpi->dev, "phy");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	uphy->cal_clk = clk = devm_clk_get(&ulpi->dev, "cal");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	uphy->cal_sleep_clk = clk = devm_clk_get(&ulpi->dev, "cal_sleep");
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	uphy->phy = devm_phy_create(&ulpi->dev, ulpi->dev.of_node,
				    &qcom_usb_hsic_phy_ops);
	if (IS_ERR(uphy->phy))
		return PTR_ERR(uphy->phy);
	phy_set_drvdata(uphy->phy, uphy);

	p = devm_of_phy_provider_register(&ulpi->dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(p);
}