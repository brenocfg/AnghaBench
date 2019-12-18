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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  a_bus_drop; } ;
struct ci_hdrc {TYPE_1__ fsm; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 unsigned int scnprintf (char*,unsigned int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
a_bus_drop_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	char		*next;
	unsigned	size, t;
	struct ci_hdrc	*ci = dev_get_drvdata(dev);

	next = buf;
	size = PAGE_SIZE;
	t = scnprintf(next, size, "%d\n", ci->fsm.a_bus_drop);
	size -= t;
	next += t;

	return PAGE_SIZE - size;
}