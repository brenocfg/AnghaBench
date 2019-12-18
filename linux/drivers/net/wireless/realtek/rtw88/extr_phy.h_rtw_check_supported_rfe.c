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
struct rtw_rfe_def {int /*<<< orphan*/  txpwr_lmt_tbl; int /*<<< orphan*/  phy_pg_tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  rfe_option; } ;
struct rtw_dev {TYPE_1__ efuse; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*,int /*<<< orphan*/ ) ; 
 struct rtw_rfe_def* rtw_get_rfe_def (struct rtw_dev*) ; 

__attribute__((used)) static inline int rtw_check_supported_rfe(struct rtw_dev *rtwdev)
{
	const struct rtw_rfe_def *rfe_def = rtw_get_rfe_def(rtwdev);

	if (!rfe_def || !rfe_def->phy_pg_tbl || !rfe_def->txpwr_lmt_tbl) {
		rtw_err(rtwdev, "rfe %d isn't supported\n",
			rtwdev->efuse.rfe_option);
		return -ENODEV;
	}

	return 0;
}