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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_hwmon_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOC_TEMP_REG ; 
 int xgene_hwmon_reg_map_rd (struct xgene_hwmon_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int xgene_hwmon_get_temp(struct xgene_hwmon_dev *ctx, u32 *val)
{
	return xgene_hwmon_reg_map_rd(ctx, SOC_TEMP_REG, val);
}