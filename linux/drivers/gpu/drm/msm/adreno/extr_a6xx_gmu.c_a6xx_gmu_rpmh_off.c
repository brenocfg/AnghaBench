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
typedef  int u32 ;
struct a6xx_gmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS0_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS1_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS2_DRV0_STATUS ; 
 int /*<<< orphan*/  REG_A6XX_RSCC_TCS3_DRV0_STATUS ; 
 int /*<<< orphan*/  gmu_poll_timeout (struct a6xx_gmu*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void a6xx_gmu_rpmh_off(struct a6xx_gmu *gmu)
{
	u32 val;

	/* Make sure there are no outstanding RPMh votes */
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS0_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS1_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS2_DRV0_STATUS, val,
		(val & 1), 100, 10000);
	gmu_poll_timeout(gmu, REG_A6XX_RSCC_TCS3_DRV0_STATUS, val,
		(val & 1), 100, 1000);
}