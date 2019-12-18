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
struct vb2_queue {struct f54_data* drv_priv; } ;
struct f54_data {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int rmi_f54_get_report_size (struct f54_data*) ; 

__attribute__((used)) static int rmi_f54_queue_setup(struct vb2_queue *q, unsigned int *nbuffers,
			       unsigned int *nplanes, unsigned int sizes[],
			       struct device *alloc_devs[])
{
	struct f54_data *f54 = q->drv_priv;

	if (*nplanes)
		return sizes[0] < rmi_f54_get_report_size(f54) ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = rmi_f54_get_report_size(f54);

	return 0;
}