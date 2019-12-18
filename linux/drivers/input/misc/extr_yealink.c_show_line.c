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
struct yealink_dev {int /*<<< orphan*/ * lcdMap; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENODEV ; 
 struct yealink_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* lcdMap ; 
 int /*<<< orphan*/  sysfs_rwsema ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t show_line(struct device *dev, char *buf, int a, int b)
{
	struct yealink_dev *yld;
	int i;

	down_read(&sysfs_rwsema);
	yld = dev_get_drvdata(dev);
	if (yld == NULL) {
		up_read(&sysfs_rwsema);
		return -ENODEV;
	}

	for (i = a; i < b; i++)
		*buf++ = lcdMap[i].type;
	*buf++ = '\n';
	for (i = a; i < b; i++)
		*buf++ = yld->lcdMap[i];
	*buf++ = '\n';
	*buf = 0;

	up_read(&sysfs_rwsema);
	return 3 + ((b - a) << 1);
}