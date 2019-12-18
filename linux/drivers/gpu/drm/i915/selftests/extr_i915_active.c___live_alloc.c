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
struct live_active {int /*<<< orphan*/  base; int /*<<< orphan*/  ref; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __live_active ; 
 int /*<<< orphan*/  __live_retire ; 
 int /*<<< orphan*/  i915_active_init (struct drm_i915_private*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct live_active* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct live_active *__live_alloc(struct drm_i915_private *i915)
{
	struct live_active *active;

	active = kzalloc(sizeof(*active), GFP_KERNEL);
	if (!active)
		return NULL;

	kref_init(&active->ref);
	i915_active_init(i915, &active->base, __live_active, __live_retire);

	return active;
}