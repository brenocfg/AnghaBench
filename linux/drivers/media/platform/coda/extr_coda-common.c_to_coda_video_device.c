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
struct video_device {int dummy; } ;
struct coda_video_device {int dummy; } ;
struct coda_dev {TYPE_1__* devtype; struct video_device* vfd; } ;
struct TYPE_2__ {unsigned int num_vdevs; struct coda_video_device const** vdevs; } ;

/* Variables and functions */
 struct coda_dev* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static const struct coda_video_device *to_coda_video_device(struct video_device
							    *vdev)
{
	struct coda_dev *dev = video_get_drvdata(vdev);
	unsigned int i = vdev - dev->vfd;

	if (i >= dev->devtype->num_vdevs)
		return NULL;

	return dev->devtype->vdevs[i];
}