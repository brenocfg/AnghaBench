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
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long dbg_level ; 
 scalar_t__ parse_strtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t debug_level_store(struct device_driver *drv, const char *buf,
				 size_t count)
{
	unsigned long t;

	if (parse_strtoul(buf, 0xffff, &t))
		return -EINVAL;

	dbg_level = t;

	return count;
}