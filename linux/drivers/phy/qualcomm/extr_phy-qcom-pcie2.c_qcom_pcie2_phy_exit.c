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
struct qcom_phy {int /*<<< orphan*/  phy_reset; int /*<<< orphan*/  vregs; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct qcom_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_pcie2_phy_exit(struct phy *phy)
{
	struct qcom_phy *qphy = phy_get_drvdata(phy);

	regulator_bulk_disable(ARRAY_SIZE(qphy->vregs), qphy->vregs);
	reset_control_assert(qphy->phy_reset);

	return 0;
}