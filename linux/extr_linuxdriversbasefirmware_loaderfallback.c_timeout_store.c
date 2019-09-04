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
struct class_attribute {int dummy; } ;
struct class {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __fw_fallback_set_timeout (int) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t timeout_store(struct class *class, struct class_attribute *attr,
			     const char *buf, size_t count)
{
	int tmp_loading_timeout = simple_strtol(buf, NULL, 10);

	if (tmp_loading_timeout < 0)
		tmp_loading_timeout = 0;

	__fw_fallback_set_timeout(tmp_loading_timeout);

	return count;
}