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
struct fdp1_q_data {TYPE_2__ format; } ;
struct fdp1_ctx {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {unsigned int sizeimage; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int FDP1_MAX_PLANES ; 
 struct fdp1_q_data* get_q_data (struct fdp1_ctx*,int /*<<< orphan*/ ) ; 
 struct fdp1_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int fdp1_queue_setup(struct vb2_queue *vq,
				unsigned int *nbuffers, unsigned int *nplanes,
				unsigned int sizes[],
				struct device *alloc_ctxs[])
{
	struct fdp1_ctx *ctx = vb2_get_drv_priv(vq);
	struct fdp1_q_data *q_data;
	unsigned int i;

	q_data = get_q_data(ctx, vq->type);

	if (*nplanes) {
		if (*nplanes > FDP1_MAX_PLANES)
			return -EINVAL;

		return 0;
	}

	*nplanes = q_data->format.num_planes;

	for (i = 0; i < *nplanes; i++)
		sizes[i] = q_data->format.plane_fmt[i].sizeimage;

	return 0;
}