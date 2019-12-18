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
struct qmp_phy {struct qcom_qmp* qmp; } ;
struct qcom_qmp {int mode; } ;
struct phy {int dummy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 struct qmp_phy* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int qcom_qmp_phy_set_mode(struct phy *phy,
				 enum phy_mode mode, int submode)
{
	struct qmp_phy *qphy = phy_get_drvdata(phy);
	struct qcom_qmp *qmp = qphy->qmp;

	qmp->mode = mode;

	return 0;
}