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
struct eeepc_laptop {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EIO ; 
 struct eeepc_laptop* dev_get_drvdata (struct device*) ; 
 int parse_arg (char const*,int*) ; 
 int set_acpi (struct eeepc_laptop*,int,int) ; 

__attribute__((used)) static ssize_t store_sys_acpi(struct device *dev, int cm,
			      const char *buf, size_t count)
{
	struct eeepc_laptop *eeepc = dev_get_drvdata(dev);
	int rv, value;

	rv = parse_arg(buf, &value);
	if (rv < 0)
		return rv;
	rv = set_acpi(eeepc, cm, value);
	if (rv < 0)
		return -EIO;
	return count;
}