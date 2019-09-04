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
struct mcb_bus {int /*<<< orphan*/  model; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mcb_bus* to_mcb_bus (struct device*) ; 

__attribute__((used)) static ssize_t model_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct mcb_bus *bus = to_mcb_bus(dev);

	return scnprintf(buf, PAGE_SIZE, "%c\n", bus->model);
}