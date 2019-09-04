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
typedef  int /*<<< orphan*/  u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 size_t EINVAL ; 
 TYPE_1__* attr_to_bank (struct device_attribute*) ; 
 scalar_t__ kstrtou64 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_restart () ; 

__attribute__((used)) static ssize_t set_bank(struct device *s, struct device_attribute *attr,
			const char *buf, size_t size)
{
	u64 new;

	if (kstrtou64(buf, 0, &new) < 0)
		return -EINVAL;

	attr_to_bank(attr)->ctl = new;
	mce_restart();

	return size;
}