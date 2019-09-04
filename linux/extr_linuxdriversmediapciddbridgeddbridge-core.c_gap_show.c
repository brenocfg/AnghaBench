#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct ddb {TYPE_2__* port; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int gap; } ;

/* Variables and functions */
 struct ddb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t gap_show(struct device *device,
			struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);
	int num = attr->attr.name[3] - 0x30;

	return sprintf(buf, "%d\n", dev->port[num].gap);
}