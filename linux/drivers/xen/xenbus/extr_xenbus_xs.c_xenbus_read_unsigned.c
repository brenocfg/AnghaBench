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

/* Variables and functions */
 int /*<<< orphan*/  XBT_NIL ; 
 int xenbus_scanf (int /*<<< orphan*/ ,char const*,char const*,char*,unsigned int*) ; 

unsigned int xenbus_read_unsigned(const char *dir, const char *node,
				  unsigned int default_val)
{
	unsigned int val;
	int ret;

	ret = xenbus_scanf(XBT_NIL, dir, node, "%u", &val);
	if (ret <= 0)
		val = default_val;

	return val;
}