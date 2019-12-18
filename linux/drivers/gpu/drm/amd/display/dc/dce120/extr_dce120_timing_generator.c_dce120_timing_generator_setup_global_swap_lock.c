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
typedef  scalar_t__ uint32_t ;
struct timing_generator {scalar_t__ inst; int /*<<< orphan*/  ctx; } ;
struct dcp_gsl_params {scalar_t__ gsl_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_GSL_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_V_TOTAL ; 
 int /*<<< orphan*/  CRTC_GSL_CHECK_LINE_NUM ; 
 int /*<<< orphan*/  CRTC_GSL_FORCE_DELAY ; 
 int /*<<< orphan*/  CRTC_REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_N (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CRTC_V_TOTAL ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL0_EN ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL_DELAY_SURFACE_UPDATE_PENDING ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_CHECK_DELAY ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_FORCE_DELAY ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL_MASTER_EN ; 
 int /*<<< orphan*/  DCP0_DCP_GSL_CONTROL__DCP_GSL_SYNC_SOURCE ; 
 int /*<<< orphan*/  FD (int /*<<< orphan*/ ) ; 
 scalar_t__ FLIP_READY_BACK_LOOKUP ; 
 int /*<<< orphan*/  HFLIP_CHECK_DELAY ; 
 int /*<<< orphan*/  HFLIP_READY_DELAY ; 
 int /*<<< orphan*/  VFLIP_READY_DELAY ; 
 scalar_t__ dm_read_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_reg_field_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_GSL_WINDOW ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_V_TOTAL ; 

void dce120_timing_generator_setup_global_swap_lock(
	struct timing_generator *tg,
	const struct dcp_gsl_params *gsl_params)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);
	uint32_t value_crtc_vtotal =
							dm_read_reg_soc15(tg->ctx,
							mmCRTC0_CRTC_V_TOTAL,
							tg110->offsets.crtc);
	/* Checkpoint relative to end of frame */
	uint32_t check_point =
							get_reg_field_value(value_crtc_vtotal,
							CRTC0_CRTC_V_TOTAL,
							CRTC_V_TOTAL);


	dm_write_reg_soc15(tg->ctx, mmCRTC0_CRTC_GSL_WINDOW, tg110->offsets.crtc, 0);

	CRTC_REG_UPDATE_N(DCP0_DCP_GSL_CONTROL, 6,
		/* This pipe will belong to GSL Group zero. */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL0_EN), 1,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_MASTER_EN), gsl_params->gsl_master == tg->inst,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_FORCE_DELAY), HFLIP_READY_DELAY,
		/* Keep signal low (pending high) during 6 lines.
		 * Also defines minimum interval before re-checking signal. */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_HSYNC_FLIP_CHECK_DELAY), HFLIP_CHECK_DELAY,
		/* DCP_GSL_PURPOSE_SURFACE_FLIP */
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_SYNC_SOURCE), 0,
		FD(DCP0_DCP_GSL_CONTROL__DCP_GSL_DELAY_SURFACE_UPDATE_PENDING), 1);

	CRTC_REG_SET_2(
			CRTC0_CRTC_GSL_CONTROL,
			CRTC_GSL_CHECK_LINE_NUM, check_point - FLIP_READY_BACK_LOOKUP,
			CRTC_GSL_FORCE_DELAY, VFLIP_READY_DELAY);
}