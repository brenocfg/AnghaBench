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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 unsigned long scroll_speed ; 

__attribute__((used)) static int param_set_scroll_speed(const char *val,
				  const struct kernel_param *kp) {
	unsigned long speed;
	if (!val || kstrtoul(val, 0, &speed) || speed > 63)
		return -EINVAL;
	scroll_speed = speed;
	return 0;
}