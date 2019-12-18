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
struct TYPE_4__ {unsigned int num_planes; TYPE_1__* plane_fmt; } ;
struct jpu_q_data {TYPE_2__ format; } ;
struct jpu_ctx {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 struct jpu_q_data* jpu_get_q_data (struct jpu_ctx*,int /*<<< orphan*/ ) ; 
 struct jpu_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int jpu_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct jpu_ctx *ctx = vb2_get_drv_priv(vq);
	struct jpu_q_data *q_data;
	unsigned int i;

	q_data = jpu_get_q_data(ctx, vq->type);

	if (*nplanes) {
		if (*nplanes != q_data->format.num_planes)
			return -EINVAL;

		for (i = 0; i < *nplanes; i++) {
			unsigned int q_size = q_data->format.plane_fmt[i].sizeimage;

			if (sizes[i] < q_size)
				return -EINVAL;
		}
		return 0;
	}

	*nplanes = q_data->format.num_planes;

	for (i = 0; i < *nplanes; i++)
		sizes[i] = q_data->format.plane_fmt[i].sizeimage;

	return 0;
}