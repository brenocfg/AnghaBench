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
 size_t EINVAL ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pkt_remove_dev (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static ssize_t remove_store(struct class *c, struct class_attribute *attr,
			    const char *buf, size_t count)
{
	unsigned int major, minor;
	if (sscanf(buf, "%u:%u", &major, &minor) == 2) {
		pkt_remove_dev(MKDEV(major, minor));
		return count;
	}
	return -EINVAL;
}