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
struct TYPE_2__ {unsigned int sizeimage; } ;
struct sta2x11_vip {scalar_t__ bcount; scalar_t__ tcount; int /*<<< orphan*/ * active; scalar_t__ sequence; TYPE_1__ format; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int MAX_FRAMES ; 
 struct sta2x11_vip* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct sta2x11_vip *vip = vb2_get_drv_priv(vq);

	if (!(*nbuffers) || *nbuffers < MAX_FRAMES)
		*nbuffers = MAX_FRAMES;

	*nplanes = 1;
	sizes[0] = vip->format.sizeimage;

	vip->sequence = 0;
	vip->active = NULL;
	vip->tcount = 0;
	vip->bcount = 0;

	return 0;
}