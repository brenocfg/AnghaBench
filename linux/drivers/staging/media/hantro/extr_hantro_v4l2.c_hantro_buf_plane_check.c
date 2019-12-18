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
struct vb2_buffer {int dummy; } ;
struct v4l2_pix_format_mplane {int num_planes; TYPE_1__* plane_fmt; } ;
struct hantro_fmt {int dummy; } ;
struct TYPE_2__ {unsigned int sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int vb2_plane_size (struct vb2_buffer*,int) ; 
 int /*<<< orphan*/  vpu_debug (int,char*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vpu_err (char*,int) ; 

__attribute__((used)) static int
hantro_buf_plane_check(struct vb2_buffer *vb, const struct hantro_fmt *vpu_fmt,
		       struct v4l2_pix_format_mplane *pixfmt)
{
	unsigned int sz;
	int i;

	for (i = 0; i < pixfmt->num_planes; ++i) {
		sz = pixfmt->plane_fmt[i].sizeimage;
		vpu_debug(4, "plane %d size: %ld, sizeimage: %u\n",
			  i, vb2_plane_size(vb, i), sz);
		if (vb2_plane_size(vb, i) < sz) {
			vpu_err("plane %d is too small for output\n", i);
			return -EINVAL;
		}
	}
	return 0;
}