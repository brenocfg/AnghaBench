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
struct em28xx_v4l2 {int width; int height; TYPE_1__* format; } ;
struct em28xx {struct em28xx_v4l2* v4l2; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int depth; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  em28xx_enable_analog_tuner (struct em28xx*) ; 
 struct em28xx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *vq,
		       unsigned int *nbuffers, unsigned int *nplanes,
		       unsigned int sizes[], struct device *alloc_devs[])
{
	struct em28xx *dev = vb2_get_drv_priv(vq);
	struct em28xx_v4l2 *v4l2 = dev->v4l2;
	unsigned long size =
		    (v4l2->width * v4l2->height * v4l2->format->depth + 7) >> 3;

	if (*nplanes)
		return sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;

	em28xx_enable_analog_tuner(dev);

	return 0;
}