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
struct imx6_pcie {int /*<<< orphan*/  apps_reset; int /*<<< orphan*/  iomuxc_gpr; TYPE_1__* drvdata; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int variant; } ;

/* Variables and functions */
#define  IMX6Q 132 
#define  IMX6QP 131 
 int /*<<< orphan*/  IMX6Q_GPR12_PCIE_CTL_2 ; 
#define  IMX6SX 130 
#define  IMX7D 129 
#define  IMX8MQ 128 
 int /*<<< orphan*/  IOMUXC_GPR12 ; 
 struct imx6_pcie* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx6_pcie_ltssm_enable(struct device *dev)
{
	struct imx6_pcie *imx6_pcie = dev_get_drvdata(dev);

	switch (imx6_pcie->drvdata->variant) {
	case IMX6Q:
	case IMX6SX:
	case IMX6QP:
		regmap_update_bits(imx6_pcie->iomuxc_gpr, IOMUXC_GPR12,
				   IMX6Q_GPR12_PCIE_CTL_2,
				   IMX6Q_GPR12_PCIE_CTL_2);
		break;
	case IMX7D:
	case IMX8MQ:
		reset_control_deassert(imx6_pcie->apps_reset);
		break;
	}
}