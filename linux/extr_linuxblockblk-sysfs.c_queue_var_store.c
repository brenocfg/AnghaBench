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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 unsigned long UINT_MAX ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t
queue_var_store(unsigned long *var, const char *page, size_t count)
{
	int err;
	unsigned long v;

	err = kstrtoul(page, 10, &v);
	if (err || v > UINT_MAX)
		return -EINVAL;

	*var = v;

	return count;
}