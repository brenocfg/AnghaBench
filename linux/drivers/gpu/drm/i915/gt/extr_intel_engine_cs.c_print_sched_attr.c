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
struct i915_sched_attr {scalar_t__ priority; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 scalar_t__ I915_PRIORITY_INVALID ; 
 scalar_t__ snprintf (char*,int,char*,scalar_t__) ; 

__attribute__((used)) static int print_sched_attr(struct drm_i915_private *i915,
			    const struct i915_sched_attr *attr,
			    char *buf, int x, int len)
{
	if (attr->priority == I915_PRIORITY_INVALID)
		return x;

	x += snprintf(buf + x, len - x,
		      " prio=%d", attr->priority);

	return x;
}