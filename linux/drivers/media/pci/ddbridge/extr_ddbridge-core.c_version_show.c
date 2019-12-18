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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ddb {TYPE_2__* link; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int hwid; int regmapid; } ;
struct TYPE_4__ {TYPE_1__ ids; } ;

/* Variables and functions */
 struct ddb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

__attribute__((used)) static ssize_t version_show(struct device *device,
			    struct device_attribute *attr, char *buf)
{
	struct ddb *dev = dev_get_drvdata(device);

	return sprintf(buf, "%08x %08x\n",
		       dev->link[0].ids.hwid, dev->link[0].ids.regmapid);
}