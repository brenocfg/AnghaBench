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
struct i915_timeline {int /*<<< orphan*/  kref; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i915_timeline* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i915_timeline_init (struct drm_i915_private*,struct i915_timeline*,char const*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct i915_timeline* kzalloc (int,int /*<<< orphan*/ ) ; 

struct i915_timeline *
i915_timeline_create(struct drm_i915_private *i915, const char *name)
{
	struct i915_timeline *timeline;

	timeline = kzalloc(sizeof(*timeline), GFP_KERNEL);
	if (!timeline)
		return ERR_PTR(-ENOMEM);

	i915_timeline_init(i915, timeline, name);
	kref_init(&timeline->kref);

	return timeline;
}