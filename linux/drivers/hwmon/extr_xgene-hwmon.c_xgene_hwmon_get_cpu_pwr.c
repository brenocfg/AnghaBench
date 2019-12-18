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
typedef  scalar_t__ u32 ;
struct xgene_hwmon_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMD_PWR_MW_REG ; 
 int /*<<< orphan*/  PMD_PWR_REG ; 
 scalar_t__ WATT_TO_mWATT (scalar_t__) ; 
 int xgene_hwmon_reg_map_rd (struct xgene_hwmon_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int xgene_hwmon_get_cpu_pwr(struct xgene_hwmon_dev *ctx, u32 *val)
{
	u32 watt, mwatt;
	int rc;

	rc = xgene_hwmon_reg_map_rd(ctx, PMD_PWR_REG, &watt);
	if (rc < 0)
		return rc;

	rc = xgene_hwmon_reg_map_rd(ctx, PMD_PWR_MW_REG, &mwatt);
	if (rc < 0)
		return rc;

	*val = WATT_TO_mWATT(watt) + mwatt;
	return 0;
}