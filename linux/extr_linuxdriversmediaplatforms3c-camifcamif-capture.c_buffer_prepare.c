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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct camif_vp {scalar_t__ payload; int /*<<< orphan*/  vdev; int /*<<< orphan*/ * out_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 struct camif_vp* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int buffer_prepare(struct vb2_buffer *vb)
{
	struct camif_vp *vp = vb2_get_drv_priv(vb->vb2_queue);

	if (vp->out_fmt == NULL)
		return -EINVAL;

	if (vb2_plane_size(vb, 0) < vp->payload) {
		v4l2_err(&vp->vdev, "buffer too small: %lu, required: %u\n",
			 vb2_plane_size(vb, 0), vp->payload);
		return -EINVAL;
	}
	vb2_set_plane_payload(vb, 0, vp->payload);

	return 0;
}