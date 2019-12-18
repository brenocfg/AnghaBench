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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ nvdimm_namespace_capacity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 int /*<<< orphan*/  to_ndns (struct device*) ; 

__attribute__((used)) static ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	return sprintf(buf, "%llu\n", (unsigned long long)
			nvdimm_namespace_capacity(to_ndns(dev)));
}