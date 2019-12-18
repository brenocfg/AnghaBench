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
struct mcif_wb {int dummy; } ;
struct mcif_arb_params {int time_per_pixel; int* cli_watermark; int* pstate_watermark; int max_scaled_time; int slice_lines; int arbitration_slice; } ;
struct dcn20_mmhubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SCALED_TIME_TO_URGENT ; 
 int /*<<< orphan*/  MCIF_WB_ARBITRATION_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_SLICE_SIZE ; 
 int /*<<< orphan*/  MCIF_WB_BUFMGR_VCE_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_CLIENT_ARBITRATION_SLICE ; 
 int /*<<< orphan*/  MCIF_WB_CLI_WATERMARK ; 
 int /*<<< orphan*/  MCIF_WB_CLI_WATERMARK_MASK ; 
 int /*<<< orphan*/  MCIF_WB_NB_PSTATE_CONTROL ; 
 int /*<<< orphan*/  MCIF_WB_NB_PSTATE_LATENCY_WATERMARK ; 
 int /*<<< orphan*/  MCIF_WB_SCLK_CHANGE ; 
 int /*<<< orphan*/  MCIF_WB_TIME_PER_PIXEL ; 
 int /*<<< orphan*/  MCIF_WB_WATERMARK ; 
 int /*<<< orphan*/  MULTI_LEVEL_QOS_CTRL ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_REFRESH_WATERMARK ; 
 int /*<<< orphan*/  NB_PSTATE_CHANGE_WATERMARK_MASK ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_mmhubbub* TO_DCN20_MMHUBBUB (struct mcif_wb*) ; 

__attribute__((used)) static void mmhubbub2_config_mcif_arb(struct mcif_wb *mcif_wb,
		struct mcif_arb_params *params)
{
	struct dcn20_mmhubbub *mcif_wb20 = TO_DCN20_MMHUBBUB(mcif_wb);

	/* Programmed by the video driver based on the CRTC timing (for DWB) */
	REG_UPDATE(MCIF_WB_ARBITRATION_CONTROL, MCIF_WB_TIME_PER_PIXEL, params->time_per_pixel);

	/* Programming dwb watermark */
	/* Watermark to generate urgent in MCIF_WB_CLI, value is determined by MCIF_WB_CLI_WATERMARK_MASK. */
	/* Program in ns. A formula will be provided in the pseudo code to calculate the value. */
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x0);
	/* urgent_watermarkA */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[0]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x1);
	/* urgent_watermarkB */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[1]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x2);
	/* urgent_watermarkC */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[2]);
	REG_UPDATE(MCIF_WB_SCLK_CHANGE, MCIF_WB_CLI_WATERMARK_MASK, 0x3);
	/* urgent_watermarkD */
	REG_UPDATE(MCIF_WB_WATERMARK, MCIF_WB_CLI_WATERMARK,  params->cli_watermark[3]);

	/* Programming nb pstate watermark */
	/* nbp_state_change_watermarkA */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x0);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[0]);
	/* nbp_state_change_watermarkB */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x1);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[1]);
	/* nbp_state_change_watermarkC */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x2);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[2]);
	/* nbp_state_change_watermarkD */
	REG_UPDATE(MCIF_WB_NB_PSTATE_CONTROL, NB_PSTATE_CHANGE_WATERMARK_MASK, 0x3);
	REG_UPDATE(MCIF_WB_NB_PSTATE_LATENCY_WATERMARK,
			NB_PSTATE_CHANGE_REFRESH_WATERMARK, params->pstate_watermark[3]);

	/* max_scaled_time */
	REG_UPDATE(MULTI_LEVEL_QOS_CTRL, MAX_SCALED_TIME_TO_URGENT, params->max_scaled_time);

	/* slice_lines */
	REG_UPDATE(MCIF_WB_BUFMGR_VCE_CONTROL, MCIF_WB_BUFMGR_SLICE_SIZE, params->slice_lines-1);

	/* Set arbitration unit for Luma/Chroma */
	/* arb_unit=2 should be chosen for more efficiency */
	/* Arbitration size, 0: 512 bytes 1: 1024 bytes 2: 2048 Bytes */
	REG_UPDATE(MCIF_WB_ARBITRATION_CONTROL, MCIF_WB_CLIENT_ARBITRATION_SLICE,  params->arbitration_slice);
}