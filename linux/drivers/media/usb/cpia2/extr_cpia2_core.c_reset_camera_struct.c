#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {scalar_t__ sensor_flags; } ;
struct TYPE_13__ {void* frame_rate; scalar_t__ gpio_data; scalar_t__ gpio_direction; scalar_t__ lowlight_boost; } ;
struct TYPE_12__ {scalar_t__ device_type; } ;
struct TYPE_11__ {int quality; } ;
struct TYPE_10__ {int creep_period; int user_squeeze; int inhibit_htables; int /*<<< orphan*/  jpeg_options; } ;
struct TYPE_9__ {int /*<<< orphan*/  flicker_mode_req; } ;
struct TYPE_16__ {TYPE_7__ roi; TYPE_6__ version; TYPE_5__ vp_params; TYPE_4__ pnp_id; TYPE_3__ vc_params; TYPE_2__ compression; TYPE_1__ flicker_control; } ;
struct camera_data {TYPE_8__ params; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  video_size; int /*<<< orphan*/  sensor_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_SENSOR_410 ; 
 int /*<<< orphan*/  CPIA2_SENSOR_500 ; 
 int /*<<< orphan*/  CPIA2_VC_VC_JPEG_OPT_DEFAULT ; 
 void* CPIA2_VP_FRAMERATE_15 ; 
 void* CPIA2_VP_FRAMERATE_30 ; 
 scalar_t__ CPIA2_VP_SENSOR_FLAGS_500 ; 
 scalar_t__ DEVICE_STV_672 ; 
 int /*<<< orphan*/  NEVER_FLICKER ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_CIF_ROWS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_COLS ; 
 int /*<<< orphan*/  STV_IMAGE_VGA_ROWS ; 
 int /*<<< orphan*/  VIDEOSIZE_CIF ; 
 int /*<<< orphan*/  VIDEOSIZE_VGA ; 

__attribute__((used)) static void reset_camera_struct(struct camera_data *cam)
{
	/***
	 * The following parameter values are the defaults from the register map.
	 ***/
	cam->params.vp_params.lowlight_boost = 0;

	/* FlickerModes */
	cam->params.flicker_control.flicker_mode_req = NEVER_FLICKER;

	/* jpeg params */
	cam->params.compression.jpeg_options = CPIA2_VC_VC_JPEG_OPT_DEFAULT;
	cam->params.compression.creep_period = 2;
	cam->params.compression.user_squeeze = 20;
	cam->params.compression.inhibit_htables = false;

	/* gpio params */
	cam->params.vp_params.gpio_direction = 0;	/* write, the default safe mode */
	cam->params.vp_params.gpio_data = 0;

	/* Target kb params */
	cam->params.vc_params.quality = 100;

	/***
	 * Set Sensor FPS as fast as possible.
	 ***/
	if(cam->params.pnp_id.device_type == DEVICE_STV_672) {
		if(cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500)
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_15;
		else
			cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	} else {
		cam->params.vp_params.frame_rate = CPIA2_VP_FRAMERATE_30;
	}

	/***
	 * Set default video mode as large as possible :
	 * for vga sensor set to vga, for cif sensor set to CIF.
	 ***/
	if (cam->params.version.sensor_flags == CPIA2_VP_SENSOR_FLAGS_500) {
		cam->sensor_type = CPIA2_SENSOR_500;
		cam->video_size = VIDEOSIZE_VGA;
		cam->params.roi.width = STV_IMAGE_VGA_COLS;
		cam->params.roi.height = STV_IMAGE_VGA_ROWS;
	} else {
		cam->sensor_type = CPIA2_SENSOR_410;
		cam->video_size = VIDEOSIZE_CIF;
		cam->params.roi.width = STV_IMAGE_CIF_COLS;
		cam->params.roi.height = STV_IMAGE_CIF_ROWS;
	}

	cam->width = cam->params.roi.width;
	cam->height = cam->params.roi.height;
}