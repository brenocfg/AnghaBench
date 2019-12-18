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
typedef  int u8 ;
struct ib_device {int use_cq_dim; } ;

/* Variables and functions */
 int EINVAL ; 

int ib_device_set_dim(struct ib_device *ibdev, u8 use_dim)
{
	if (use_dim > 1)
		return -EINVAL;
	ibdev->use_cq_dim = use_dim;

	return 0;
}