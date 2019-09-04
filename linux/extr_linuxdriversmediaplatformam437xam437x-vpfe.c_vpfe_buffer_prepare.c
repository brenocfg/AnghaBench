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
struct TYPE_6__ {int /*<<< orphan*/  field; int /*<<< orphan*/  sizeimage; } ;
struct TYPE_5__ {TYPE_3__ pix; } ;
struct TYPE_4__ {TYPE_2__ fmt; } ;
struct vpfe_device {TYPE_1__ fmt; } ;
struct vb2_v4l2_buffer {int /*<<< orphan*/  field; } ;
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vb2_v4l2_buffer* to_vb2_v4l2_buffer (struct vb2_buffer*) ; 
 struct vpfe_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_get_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_buffer_prepare(struct vb2_buffer *vb)
{
	struct vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	struct vpfe_device *vpfe = vb2_get_drv_priv(vb->vb2_queue);

	vb2_set_plane_payload(vb, 0, vpfe->fmt.fmt.pix.sizeimage);

	if (vb2_get_plane_payload(vb, 0) > vb2_plane_size(vb, 0))
		return -EINVAL;

	vbuf->field = vpfe->fmt.fmt.pix.field;

	return 0;
}