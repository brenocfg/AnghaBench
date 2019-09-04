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
struct fpga_region {TYPE_1__* compat_id; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ id_l; scalar_t__ id_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long,unsigned long long) ; 
 struct fpga_region* to_fpga_region (struct device*) ; 

__attribute__((used)) static ssize_t compat_id_show(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct fpga_region *region = to_fpga_region(dev);

	if (!region->compat_id)
		return -ENOENT;

	return sprintf(buf, "%016llx%016llx\n",
		       (unsigned long long)region->compat_id->id_h,
		       (unsigned long long)region->compat_id->id_l);
}