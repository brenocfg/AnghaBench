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
struct device {int dummy; } ;
struct container_dev {int (* offline ) (struct container_dev*) ;} ;

/* Variables and functions */
 int stub1 (struct container_dev*) ; 
 struct container_dev* to_container_dev (struct device*) ; 

__attribute__((used)) static int container_offline(struct device *dev)
{
	struct container_dev *cdev = to_container_dev(dev);

	return cdev->offline ? cdev->offline(cdev) : 0;
}