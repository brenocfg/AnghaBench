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
struct timing_generator {int dummy; } ;
struct optc {int dummy; } ;
struct crc_params {int /*<<< orphan*/  selection; scalar_t__ continuous_mode; int /*<<< orphan*/  windowb_y_end; int /*<<< orphan*/  windowb_y_start; int /*<<< orphan*/  windowb_x_end; int /*<<< orphan*/  windowb_x_start; int /*<<< orphan*/  windowa_y_end; int /*<<< orphan*/  windowa_y_start; int /*<<< orphan*/  windowa_x_end; int /*<<< orphan*/  windowa_x_start; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_CRC0_SELECT ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_X_CONTROL ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_X_END ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_X_START ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_Y_CONTROL ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_Y_END ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWA_Y_START ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_X_CONTROL ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_X_END ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_X_START ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_Y_CONTROL ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_Y_END ; 
 int /*<<< orphan*/  OTG_CRC0_WINDOWB_Y_START ; 
 int /*<<< orphan*/  OTG_CRC_CNTL ; 
 int /*<<< orphan*/  OTG_CRC_CONT_EN ; 
 int /*<<< orphan*/  OTG_CRC_EN ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optc1_is_tg_enabled (struct timing_generator*) ; 

bool optc1_configure_crc(struct timing_generator *optc,
			  const struct crc_params *params)
{
	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	/* Cannot configure crc on a CRTC that is disabled */
	if (!optc1_is_tg_enabled(optc))
		return false;

	REG_WRITE(OTG_CRC_CNTL, 0);

	if (!params->enable)
		return true;

	/* Program frame boundaries */
	/* Window A x axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWA_X_CONTROL,
			OTG_CRC0_WINDOWA_X_START, params->windowa_x_start,
			OTG_CRC0_WINDOWA_X_END, params->windowa_x_end);

	/* Window A y axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWA_Y_CONTROL,
			OTG_CRC0_WINDOWA_Y_START, params->windowa_y_start,
			OTG_CRC0_WINDOWA_Y_END, params->windowa_y_end);

	/* Window B x axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWB_X_CONTROL,
			OTG_CRC0_WINDOWB_X_START, params->windowb_x_start,
			OTG_CRC0_WINDOWB_X_END, params->windowb_x_end);

	/* Window B y axis start and end. */
	REG_UPDATE_2(OTG_CRC0_WINDOWB_Y_CONTROL,
			OTG_CRC0_WINDOWB_Y_START, params->windowb_y_start,
			OTG_CRC0_WINDOWB_Y_END, params->windowb_y_end);

	/* Set crc mode and selection, and enable. Only using CRC0*/
	REG_UPDATE_3(OTG_CRC_CNTL,
			OTG_CRC_CONT_EN, params->continuous_mode ? 1 : 0,
			OTG_CRC0_SELECT, params->selection,
			OTG_CRC_EN, 1);

	return true;
}