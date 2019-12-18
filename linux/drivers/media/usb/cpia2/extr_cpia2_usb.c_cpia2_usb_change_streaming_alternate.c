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
struct TYPE_3__ {unsigned int stream_mode; } ;
struct TYPE_4__ {TYPE_1__ camera_state; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int USBIF_ISO_1 ; 
 unsigned int USBIF_ISO_6 ; 
 int /*<<< orphan*/  configure_transfer_mode (struct camera_data*,unsigned int) ; 
 int /*<<< orphan*/  cpia2_reset_camera (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_pause (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_resume (struct camera_data*) ; 

int cpia2_usb_change_streaming_alternate(struct camera_data *cam,
					 unsigned int alt)
{
	int ret = 0;

	if(alt < USBIF_ISO_1 || alt > USBIF_ISO_6)
		return -EINVAL;

	if(alt == cam->params.camera_state.stream_mode)
		return 0;

	cpia2_usb_stream_pause(cam);

	configure_transfer_mode(cam, alt);

	cam->params.camera_state.stream_mode = alt;

	/* Reset the camera to prevent image quality degradation */
	cpia2_reset_camera(cam);

	cpia2_usb_stream_resume(cam);

	return ret;
}