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
struct a6xx_gmu {int idle_level; } ;

/* Variables and functions */
 int A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_HM_POWER_COLLAPSE_ENABLE ; 
 int A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_IFPC_ENABLE ; 
 int A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_SPTPRAC_POWER_CONTROL_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_CX_VOTE_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_DDR_VOTE_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_GFX_VOTE_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_LLC_VOTE_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_MX_VOTE_ENABLE ; 
 int A6XX_GMU_RPMH_CTRL_RPMH_INTERFACE_ENABLE ; 
#define  GMU_IDLE_STATE_IFPC 129 
#define  GMU_IDLE_STATE_SPTP 128 
 int GMU_PWR_COL_HYST ; 
 int /*<<< orphan*/  REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL ; 
 int /*<<< orphan*/  REG_A6XX_GMU_PWR_COL_INTER_FRAME_HYST ; 
 int /*<<< orphan*/  REG_A6XX_GMU_PWR_COL_SPTPRAC_HYST ; 
 int /*<<< orphan*/  REG_A6XX_GMU_RPMH_CTRL ; 
 int /*<<< orphan*/  REG_A6XX_GMU_SYS_BUS_CONFIG ; 
 int /*<<< orphan*/  gmu_rmw (struct a6xx_gmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gmu_write (struct a6xx_gmu*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void a6xx_gmu_power_config(struct a6xx_gmu *gmu)
{
	/* Disable GMU WB/RB buffer */
	gmu_write(gmu, REG_A6XX_GMU_SYS_BUS_CONFIG, 0x1);

	gmu_write(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0x9c40400);

	switch (gmu->idle_level) {
	case GMU_IDLE_STATE_IFPC:
		gmu_write(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_HYST,
			GMU_PWR_COL_HYST);
		gmu_rmw(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0,
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_IFPC_ENABLE |
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_HM_POWER_COLLAPSE_ENABLE);
		/* Fall through */
	case GMU_IDLE_STATE_SPTP:
		gmu_write(gmu, REG_A6XX_GMU_PWR_COL_SPTPRAC_HYST,
			GMU_PWR_COL_HYST);
		gmu_rmw(gmu, REG_A6XX_GMU_PWR_COL_INTER_FRAME_CTRL, 0,
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_IFPC_ENABLE |
			A6XX_GMU_PWR_COL_INTER_FRAME_CTRL_SPTPRAC_POWER_CONTROL_ENABLE);
	}

	/* Enable RPMh GPU client */
	gmu_rmw(gmu, REG_A6XX_GMU_RPMH_CTRL, 0,
		A6XX_GMU_RPMH_CTRL_RPMH_INTERFACE_ENABLE |
		A6XX_GMU_RPMH_CTRL_LLC_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_DDR_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_MX_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_CX_VOTE_ENABLE |
		A6XX_GMU_RPMH_CTRL_GFX_VOTE_ENABLE);
}