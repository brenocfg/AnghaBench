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
typedef  size_t ssize_t ;
struct TYPE_2__ {unsigned long key_count; } ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long key_at_index ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 TYPE_1__ smcreg ; 

__attribute__((used)) static ssize_t applesmc_key_at_index_store(struct device *dev,
	struct device_attribute *attr, const char *sysfsbuf, size_t count)
{
	unsigned long newkey;

	if (kstrtoul(sysfsbuf, 10, &newkey) < 0
	    || newkey >= smcreg.key_count)
		return -EINVAL;

	key_at_index = newkey;
	return count;
}