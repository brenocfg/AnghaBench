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
typedef  int ssize_t ;

/* Variables and functions */
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t nullb_device_ulong_attr_store(unsigned long *val,
	const char *page, size_t count)
{
	int result;
	unsigned long tmp;

	result = kstrtoul(page, 0, &tmp);
	if (result)
		return result;

	*val = tmp;
	return count;
}