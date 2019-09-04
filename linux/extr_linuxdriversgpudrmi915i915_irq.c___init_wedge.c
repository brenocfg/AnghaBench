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
struct wedge_me {char const* name; int /*<<< orphan*/  work; struct drm_i915_private* i915; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK_ONSTACK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  wedge_me ; 

__attribute__((used)) static void __init_wedge(struct wedge_me *w,
			 struct drm_i915_private *i915,
			 long timeout,
			 const char *name)
{
	w->i915 = i915;
	w->name = name;

	INIT_DELAYED_WORK_ONSTACK(&w->work, wedge_me);
	schedule_delayed_work(&w->work, timeout);
}