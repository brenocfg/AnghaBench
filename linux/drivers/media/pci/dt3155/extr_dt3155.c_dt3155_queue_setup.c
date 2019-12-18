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
struct vb2_queue {unsigned int num_buffers; } ;
struct dt3155_priv {unsigned int width; unsigned int height; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dt3155_priv* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int
dt3155_queue_setup(struct vb2_queue *vq,
		unsigned int *nbuffers, unsigned int *num_planes,
		unsigned int sizes[], struct device *alloc_devs[])

{
	struct dt3155_priv *pd = vb2_get_drv_priv(vq);
	unsigned size = pd->width * pd->height;

	if (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;
	if (*num_planes)
		return sizes[0] < size ? -EINVAL : 0;
	*num_planes = 1;
	sizes[0] = size;
	return 0;
}