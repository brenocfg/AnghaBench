#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int expMode; } ;
struct TYPE_4__ {TYPE_1__ exposure; } ;
struct sd {scalar_t__ first_frame; TYPE_2__ params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetExposure ; 
 int /*<<< orphan*/  CPIA_COMMAND_ReadMCPorts ; 
 int /*<<< orphan*/  command_setcompression (struct gspca_dev*) ; 
 int /*<<< orphan*/  do_command (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_exposure (struct gspca_dev*) ; 
 int /*<<< orphan*/  restart_flicker (struct gspca_dev*) ; 

__attribute__((used)) static void sd_dq_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	/* Set the normal compression settings once we have captured a
	   few uncompressed frames (and AEC has hopefully settled) */
	if (sd->first_frame) {
		sd->first_frame--;
		if (sd->first_frame == 0)
			command_setcompression(gspca_dev);
	}

	/* Switch flicker control back on if it got turned off */
	restart_flicker(gspca_dev);

	/* If AEC is enabled, monitor the exposure and
	   adjust the sensor frame rate if needed */
	if (sd->params.exposure.expMode == 2)
		monitor_exposure(gspca_dev);

	/* Update our knowledge of the camera state */
	do_command(gspca_dev, CPIA_COMMAND_GetExposure, 0, 0, 0, 0);
	do_command(gspca_dev, CPIA_COMMAND_ReadMCPorts, 0, 0, 0, 0);
}