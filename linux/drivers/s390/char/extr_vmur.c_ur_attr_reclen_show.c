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
struct urdev {int /*<<< orphan*/  reclen; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ENODEV ; 
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 
 struct urdev* urdev_get_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urdev_put (struct urdev*) ; 

__attribute__((used)) static ssize_t ur_attr_reclen_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct urdev *urd;
	int rc;

	urd = urdev_get_from_cdev(to_ccwdev(dev));
	if (!urd)
		return -ENODEV;
	rc = sprintf(buf, "%zu\n", urd->reclen);
	urdev_put(urd);
	return rc;
}