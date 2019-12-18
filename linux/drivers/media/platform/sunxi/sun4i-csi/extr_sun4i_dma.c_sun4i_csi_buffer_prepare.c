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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_4__ {unsigned int num_planes; TYPE_1__* plane_fmt; } ;
struct sun4i_csi {int /*<<< orphan*/  dev; TYPE_2__ fmt; } ;
struct TYPE_3__ {unsigned long sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 struct sun4i_csi* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned long vb2_plane_size (struct vb2_buffer*,unsigned int) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,unsigned int,unsigned long) ; 

__attribute__((used)) static int sun4i_csi_buffer_prepare(struct vb2_buffer *vb)
{
	struct sun4i_csi *csi = vb2_get_drv_priv(vb->vb2_queue);
	unsigned int i;

	for (i = 0; i < csi->fmt.num_planes; i++) {
		unsigned long size = csi->fmt.plane_fmt[i].sizeimage;

		if (vb2_plane_size(vb, i) < size) {
			dev_err(csi->dev, "buffer too small (%lu < %lu)\n",
				vb2_plane_size(vb, i), size);
			return -EINVAL;
		}

		vb2_set_plane_payload(vb, i, size);
	}

	return 0;
}