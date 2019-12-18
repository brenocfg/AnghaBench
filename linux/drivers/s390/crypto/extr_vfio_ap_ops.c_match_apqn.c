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
struct vfio_ap_queue {int apqn; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct vfio_ap_queue* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int match_apqn(struct device *dev, const void *data)
{
	struct vfio_ap_queue *q = dev_get_drvdata(dev);

	return (q->apqn == *(int *)(data)) ? 1 : 0;
}