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
struct imx6_pcie {int controller_id; TYPE_1__* drvdata; } ;
struct TYPE_2__ {scalar_t__ variant; } ;

/* Variables and functions */
 scalar_t__ IMX8MQ ; 
 unsigned int IOMUXC_GPR14 ; 
 unsigned int IOMUXC_GPR16 ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static unsigned int imx6_pcie_grp_offset(const struct imx6_pcie *imx6_pcie)
{
	WARN_ON(imx6_pcie->drvdata->variant != IMX8MQ);
	return imx6_pcie->controller_id == 1 ? IOMUXC_GPR16 : IOMUXC_GPR14;
}