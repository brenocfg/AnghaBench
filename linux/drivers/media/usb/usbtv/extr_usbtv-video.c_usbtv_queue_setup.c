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
typedef  int /*<<< orphan*/  u32 ;
struct vb2_queue {unsigned int num_buffers; } ;
struct usbtv {int n_chunks; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int USBTV_CHUNK ; 
 struct usbtv* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int usbtv_queue_setup(struct vb2_queue *vq,
	unsigned int *nbuffers,
	unsigned int *nplanes, unsigned int sizes[], struct device *alloc_devs[])
{
	struct usbtv *usbtv = vb2_get_drv_priv(vq);
	unsigned size = USBTV_CHUNK * usbtv->n_chunks * 2 * sizeof(u32);

	if (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;
	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;

	return 0;
}