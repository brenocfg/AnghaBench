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
struct vio_dev {struct device_node* dp; } ;
struct device_node {char* full_name; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static ssize_t
show_pciobppath_attr(struct device *dev, struct device_attribute *attr,
		     char *buf)
{
	struct vio_dev *vdev;
	struct device_node *dp;

	vdev = to_vio_dev(dev);
	dp = vdev->dp;

	return snprintf (buf, PAGE_SIZE, "%s\n", dp->full_name);
}