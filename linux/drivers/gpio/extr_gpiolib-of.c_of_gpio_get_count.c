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
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  propname ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 int ENOENT ; 
 char** gpio_suffixes ; 
 int of_gpio_named_count (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

int of_gpio_get_count(struct device *dev, const char *con_id)
{
	int ret;
	char propname[32];
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(gpio_suffixes); i++) {
		if (con_id)
			snprintf(propname, sizeof(propname), "%s-%s",
				 con_id, gpio_suffixes[i]);
		else
			snprintf(propname, sizeof(propname), "%s",
				 gpio_suffixes[i]);

		ret = of_gpio_named_count(dev->of_node, propname);
		if (ret > 0)
			break;
	}
	return ret ? ret : -ENOENT;
}