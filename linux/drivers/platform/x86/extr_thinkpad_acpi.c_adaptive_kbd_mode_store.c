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
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LAYFLAT_MODE ; 
 int adaptive_keyboard_set_mode (unsigned long) ; 
 scalar_t__ parse_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t adaptive_kbd_mode_store(struct device *dev,
			    struct device_attribute *attr,
			    const char *buf, size_t count)
{
	unsigned long t;
	int res;

	if (parse_strtoul(buf, LAYFLAT_MODE, &t))
		return -EINVAL;

	res = adaptive_keyboard_set_mode(t);
	return (res < 0) ? res : count;
}