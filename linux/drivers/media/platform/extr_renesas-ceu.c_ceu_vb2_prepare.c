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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct v4l2_pix_format_mplane {unsigned int num_planes; TYPE_1__* plane_fmt; } ;
struct ceu_device {int /*<<< orphan*/  dev; struct v4l2_pix_format_mplane v4l2_pix; } ;
struct TYPE_2__ {scalar_t__ sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 struct ceu_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_size (struct vb2_buffer*,unsigned int) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,unsigned int,scalar_t__) ; 

__attribute__((used)) static int ceu_vb2_prepare(struct vb2_buffer *vb)
{
	struct ceu_device *ceudev = vb2_get_drv_priv(vb->vb2_queue);
	struct v4l2_pix_format_mplane *pix = &ceudev->v4l2_pix;
	unsigned int i;

	for (i = 0; i < pix->num_planes; i++) {
		if (vb2_plane_size(vb, i) < pix->plane_fmt[i].sizeimage) {
			dev_err(ceudev->dev,
				"Plane size too small (%lu < %u)\n",
				vb2_plane_size(vb, i),
				pix->plane_fmt[i].sizeimage);
			return -EINVAL;
		}

		vb2_set_plane_payload(vb, i, pix->plane_fmt[i].sizeimage);
	}

	return 0;
}