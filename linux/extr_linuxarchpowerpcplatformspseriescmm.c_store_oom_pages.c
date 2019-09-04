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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EBADMSG ; 
 size_t EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ oom_freed_pages ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ssize_t store_oom_pages(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	unsigned long val = simple_strtoul (buf, NULL, 10);

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (val != 0)
		return -EBADMSG;

	oom_freed_pages = 0;
	return count;
}