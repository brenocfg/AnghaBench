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
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;
struct camif_frame {int f_width; int f_height; } ;
struct camif_vp {struct camif_fmt* out_fmt; struct camif_frame out_frame; } ;
struct camif_fmt {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 struct camif_vp* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *num_buffers, unsigned int *num_planes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct camif_vp *vp = vb2_get_drv_priv(vq);
	struct camif_frame *frame = &vp->out_frame;
	const struct camif_fmt *fmt = vp->out_fmt;
	unsigned int size;

	if (fmt == NULL)
		return -EINVAL;

	size = (frame->f_width * frame->f_height * fmt->depth) / 8;

	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;

	*num_planes = 1;
	sizes[0] = size;

	pr_debug("size: %u\n", sizes[0]);
	return 0;
}