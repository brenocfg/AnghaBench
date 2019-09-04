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
struct hidma_dev {int chidx; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct hidma_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t hidma_show_values(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct hidma_dev *mdev = dev_get_drvdata(dev);

	buf[0] = 0;

	if (strcmp(attr->attr.name, "chid") == 0)
		sprintf(buf, "%d\n", mdev->chidx);

	return strlen(buf);
}