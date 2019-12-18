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
struct gb_module {int /*<<< orphan*/  num_interfaces; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 struct gb_module* to_gb_module (struct device*) ; 

__attribute__((used)) static ssize_t num_interfaces_show(struct device *dev,
				   struct device_attribute *attr, char *buf)
{
	struct gb_module *module = to_gb_module(dev);

	return sprintf(buf, "%zu\n", module->num_interfaces);
}