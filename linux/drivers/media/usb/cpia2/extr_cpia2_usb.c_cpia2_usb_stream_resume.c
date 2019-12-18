#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  user_effects; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_6__ {TYPE_2__ vp_params; TYPE_1__ camera_state; } ;
struct camera_data {TYPE_3__ params; scalar_t__ first_image_seen; scalar_t__ streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_SET_USER_EFFECTS ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int set_alternate (struct camera_data*,int /*<<< orphan*/ ) ; 
 int submit_urbs (struct camera_data*) ; 

int cpia2_usb_stream_resume(struct camera_data *cam)
{
	int ret = 0;
	if(cam->streaming) {
		cam->first_image_seen = 0;
		ret = set_alternate(cam, cam->params.camera_state.stream_mode);
		if(ret == 0) {
			/* for some reason the user effects need to be set
			   again when starting streaming. */
			cpia2_do_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
					cam->params.vp_params.user_effects);
			ret = submit_urbs(cam);
		}
	}
	return ret;
}