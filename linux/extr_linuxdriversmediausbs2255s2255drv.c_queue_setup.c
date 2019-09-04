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
struct vb2_queue {int dummy; } ;
struct s2255_vc {int width; int height; TYPE_1__* fmt; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 unsigned int S2255_MIN_BUFS ; 
 struct s2255_vc* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct s2255_vc *vc = vb2_get_drv_priv(vq);
	if (*nbuffers < S2255_MIN_BUFS)
		*nbuffers = S2255_MIN_BUFS;
	*nplanes = 1;
	sizes[0] = vc->width * vc->height * (vc->fmt->depth >> 3);
	return 0;
}