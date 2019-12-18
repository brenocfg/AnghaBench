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
struct qcom_phy {int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  vregs; int /*<<< orphan*/  dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct qcom_phy* phy_get_drvdata (struct phy*) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_pcie2_phy_init(struct phy *phy)
{
	struct qcom_phy *qphy = phy_get_drvdata(phy);
	int ret;

	ret = reset_control_deassert(qphy->phy_reset);
	if (ret) {
		dev_err(qphy->dev, "cannot deassert pipe reset\n");
		return ret;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(qphy->vregs), qphy->vregs);
	if (ret)
		reset_control_assert(qphy->phy_reset);

	return ret;
}