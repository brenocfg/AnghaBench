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
struct TYPE_2__ {scalar_t__ sizeimage; } ;
struct via_camera {TYPE_1__ user_format; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cam_dbg (struct via_camera*,char*,scalar_t__,scalar_t__) ; 
 struct via_camera* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int viacam_vb2_prepare(struct vb2_buffer *vb)
{
	struct via_camera *cam = vb2_get_drv_priv(vb->vb2_queue);

	if (vb2_plane_size(vb, 0) < cam->user_format.sizeimage) {
		cam_dbg(cam,
			"Plane size too small (%lu < %u)\n",
			vb2_plane_size(vb, 0),
			cam->user_format.sizeimage);
		return -EINVAL;
	}

	vb2_set_plane_payload(vb, 0, cam->user_format.sizeimage);

	return 0;
}