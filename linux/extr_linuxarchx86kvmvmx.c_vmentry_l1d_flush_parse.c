#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  option; scalar_t__ for_parse; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ sysfs_streq (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmentry_l1d_param ; 

__attribute__((used)) static int vmentry_l1d_flush_parse(const char *s)
{
	unsigned int i;

	if (s) {
		for (i = 0; i < ARRAY_SIZE(vmentry_l1d_param); i++) {
			if (vmentry_l1d_param[i].for_parse &&
			    sysfs_streq(s, vmentry_l1d_param[i].option))
				return i;
		}
	}
	return -EINVAL;
}