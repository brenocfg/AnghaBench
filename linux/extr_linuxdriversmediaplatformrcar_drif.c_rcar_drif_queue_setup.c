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
struct vb2_queue {unsigned int num_buffers; } ;
struct rcar_drif_sdr {TYPE_1__* fmt; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffersize; } ;

/* Variables and functions */
 unsigned int PAGE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdrif_dbg (struct rcar_drif_sdr*,char*,unsigned int,unsigned int) ; 
 struct rcar_drif_sdr* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int rcar_drif_queue_setup(struct vb2_queue *vq,
			unsigned int *num_buffers, unsigned int *num_planes,
			unsigned int sizes[], struct device *alloc_devs[])
{
	struct rcar_drif_sdr *sdr = vb2_get_drv_priv(vq);

	/* Need at least 16 buffers */
	if (vq->num_buffers + *num_buffers < 16)
		*num_buffers = 16 - vq->num_buffers;

	*num_planes = 1;
	sizes[0] = PAGE_ALIGN(sdr->fmt->buffersize);
	rdrif_dbg(sdr, "num_bufs %d sizes[0] %d\n", *num_buffers, sizes[0]);

	return 0;
}