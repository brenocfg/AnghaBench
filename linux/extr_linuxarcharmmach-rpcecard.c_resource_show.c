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
struct expansion_card {TYPE_1__* resource; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int start; int end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct expansion_card* ECARD_DEV (struct device*) ; 
 int ECARD_NUM_RESOURCES ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t resource_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct expansion_card *ec = ECARD_DEV(dev);
	char *str = buf;
	int i;

	for (i = 0; i < ECARD_NUM_RESOURCES; i++)
		str += sprintf(str, "%08x %08x %08lx\n",
				ec->resource[i].start,
				ec->resource[i].end,
				ec->resource[i].flags);

	return str - buf;
}