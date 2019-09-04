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
struct vsp1_histogram {unsigned int data_size; } ;
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vsp1_histogram* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int histo_queue_setup(struct vb2_queue *vq, unsigned int *nbuffers,
			     unsigned int *nplanes, unsigned int sizes[],
			     struct device *alloc_devs[])
{
	struct vsp1_histogram *histo = vb2_get_drv_priv(vq);

	if (*nplanes) {
		if (*nplanes != 1)
			return -EINVAL;

		if (sizes[0] < histo->data_size)
			return -EINVAL;

		return 0;
	}

	*nplanes = 1;
	sizes[0] = histo->data_size;

	return 0;
}