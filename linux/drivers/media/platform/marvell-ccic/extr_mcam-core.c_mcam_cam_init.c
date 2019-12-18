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
struct mcam_camera {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ S_IDLE ; 
 scalar_t__ S_NOTREADY ; 
 int __mcam_cam_reset (struct mcam_camera*) ; 
 int /*<<< orphan*/  cam_warn (struct mcam_camera*,char*,scalar_t__) ; 

__attribute__((used)) static int mcam_cam_init(struct mcam_camera *cam)
{
	int ret;

	if (cam->state != S_NOTREADY)
		cam_warn(cam, "Cam init with device in funky state %d",
				cam->state);
	ret = __mcam_cam_reset(cam);
	/* Get/set parameters? */
	cam->state = S_IDLE;
	return ret;
}