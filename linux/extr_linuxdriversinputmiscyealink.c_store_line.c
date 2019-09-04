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
struct yealink_dev {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t ENODEV ; 
 struct yealink_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setChar (struct yealink_dev*,int /*<<< orphan*/ ,char const) ; 
 int /*<<< orphan*/  sysfs_rwsema ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t store_line(struct device *dev, const char *buf, size_t count,
		int el, size_t len)
{
	struct yealink_dev *yld;
	int i;

	down_write(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	if (yld == NULL) {
		up_write(&sysfs_rwsema);
		return -ENODEV;
	}

	if (len > count)
		len = count;
	for (i = 0; i < len; i++)
		setChar(yld, el++, buf[i]);

	up_write(&sysfs_rwsema);
	return count;
}