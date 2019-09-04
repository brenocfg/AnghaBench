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
struct TYPE_2__ {unsigned int sizeimage; } ;
struct sur40_state {TYPE_1__ pix_fmt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct sur40_state* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int sur40_queue_setup(struct vb2_queue *q,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct sur40_state *sur40 = vb2_get_drv_priv(q);

	if (q->num_buffers + *nbuffers < 3)
		*nbuffers = 3 - q->num_buffers;

	if (*nplanes)
		return sizes[0] < sur40->pix_fmt.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = sur40->pix_fmt.sizeimage;

	return 0;
}