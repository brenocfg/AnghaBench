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
 size_t ENODEV ; 
 int /*<<< orphan*/  MKDEV (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_setup_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t add_store(struct class *c, struct class_attribute *attr,
			 const char *buf, size_t count)
{
	unsigned int major, minor;

	if (sscanf(buf, "%u:%u", &major, &minor) == 2) {
		/* pkt_setup_dev() expects caller to hold reference to self */
		if (!try_module_get(THIS_MODULE))
			return -ENODEV;

		pkt_setup_dev(MKDEV(major, minor), NULL);

		module_put(THIS_MODULE);

		return count;
	}

	return -EINVAL;
}