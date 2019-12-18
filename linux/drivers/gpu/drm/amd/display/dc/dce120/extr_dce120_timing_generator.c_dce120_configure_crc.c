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
struct timing_generator {int /*<<< orphan*/  ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; } ;
struct dce110_timing_generator {TYPE_1__ offsets; } ;
struct crc_params {int /*<<< orphan*/  selection; scalar_t__ continuous_mode; int /*<<< orphan*/  windowb_y_end; int /*<<< orphan*/  windowb_y_start; int /*<<< orphan*/  windowb_x_end; int /*<<< orphan*/  windowb_x_start; int /*<<< orphan*/  windowa_y_end; int /*<<< orphan*/  windowa_y_start; int /*<<< orphan*/  windowa_x_end; int /*<<< orphan*/  windowa_x_start; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRTC0_CRTC_CRC0_WINDOWA_X_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_CRC0_WINDOWA_Y_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_CRC0_WINDOWB_X_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_CRC0_WINDOWB_Y_CONTROL ; 
 int /*<<< orphan*/  CRTC0_CRTC_CRC_CNTL ; 
 int /*<<< orphan*/  CRTC_CRC0_SELECT ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWA_X_END ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWA_X_START ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWA_Y_END ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWA_Y_START ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWB_X_END ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWB_X_START ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWB_Y_END ; 
 int /*<<< orphan*/  CRTC_CRC0_WINDOWB_Y_START ; 
 int /*<<< orphan*/  CRTC_CRC_EN ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRTC_REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dce110_timing_generator* DCE110TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  dce120_is_tg_enabled (struct timing_generator*) ; 
 int /*<<< orphan*/  dm_write_reg_soc15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCRTC0_CRTC_CRC_CNTL ; 

__attribute__((used)) static bool dce120_configure_crc(struct timing_generator *tg,
				 const struct crc_params *params)
{
	struct dce110_timing_generator *tg110 = DCE110TG_FROM_TG(tg);

	/* Cannot configure crc on a CRTC that is disabled */
	if (!dce120_is_tg_enabled(tg))
		return false;

	/* First, disable CRC before we configure it. */
	dm_write_reg_soc15(tg->ctx, mmCRTC0_CRTC_CRC_CNTL,
			   tg110->offsets.crtc, 0);

	if (!params->enable)
		return true;

	/* Program frame boundaries */
	/* Window A x axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWA_X_CONTROL,
			  CRTC_CRC0_WINDOWA_X_START, params->windowa_x_start,
			  CRTC_CRC0_WINDOWA_X_END, params->windowa_x_end);

	/* Window A y axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWA_Y_CONTROL,
			  CRTC_CRC0_WINDOWA_Y_START, params->windowa_y_start,
			  CRTC_CRC0_WINDOWA_Y_END, params->windowa_y_end);

	/* Window B x axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWB_X_CONTROL,
			  CRTC_CRC0_WINDOWB_X_START, params->windowb_x_start,
			  CRTC_CRC0_WINDOWB_X_END, params->windowb_x_end);

	/* Window B y axis start and end. */
	CRTC_REG_UPDATE_2(CRTC0_CRTC_CRC0_WINDOWB_Y_CONTROL,
			  CRTC_CRC0_WINDOWB_Y_START, params->windowb_y_start,
			  CRTC_CRC0_WINDOWB_Y_END, params->windowb_y_end);

	/* Set crc mode and selection, and enable. Only using CRC0*/
	CRTC_REG_UPDATE_3(CRTC0_CRTC_CRC_CNTL,
			  CRTC_CRC_EN, params->continuous_mode ? 1 : 0,
			  CRTC_CRC0_SELECT, params->selection,
			  CRTC_CRC_EN, 1);

	return true;
}