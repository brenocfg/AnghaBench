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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {unsigned int height; } ;
struct sh_veu_vfmt {unsigned int bytesperline; TYPE_2__* fmt; TYPE_1__ frame; } ;
struct sh_veu_dev {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {unsigned int depth; unsigned int ydepth; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int VIDEO_MEM_LIMIT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 struct sh_veu_vfmt* sh_veu_get_vfmt (struct sh_veu_dev*,int /*<<< orphan*/ ) ; 
 struct sh_veu_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int sh_veu_queue_setup(struct vb2_queue *vq,
			      unsigned int *nbuffers, unsigned int *nplanes,
			      unsigned int sizes[], struct device *alloc_devs[])
{
	struct sh_veu_dev *veu = vb2_get_drv_priv(vq);
	struct sh_veu_vfmt *vfmt = sh_veu_get_vfmt(veu, vq->type);
	unsigned int count = *nbuffers;
	unsigned int size = vfmt->bytesperline * vfmt->frame.height *
		vfmt->fmt->depth / vfmt->fmt->ydepth;

	if (count < 2)
		*nbuffers = count = 2;

	if (size * count > VIDEO_MEM_LIMIT) {
		count = VIDEO_MEM_LIMIT / size;
		*nbuffers = count;
	}

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = size;

	dev_dbg(veu->dev, "get %d buffer(s) of size %d each.\n", count, size);

	return 0;
}