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
struct i915_gpu_state {struct drm_i915_private* i915; int /*<<< orphan*/  ref; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  capture ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct i915_gpu_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_machine (int /*<<< orphan*/ ,struct i915_gpu_state*,int /*<<< orphan*/ *) ; 

struct i915_gpu_state *
i915_capture_gpu_state(struct drm_i915_private *i915)
{
	struct i915_gpu_state *error;

	error = kzalloc(sizeof(*error), GFP_ATOMIC);
	if (!error)
		return NULL;

	kref_init(&error->ref);
	error->i915 = i915;

	stop_machine(capture, error, NULL);

	return error;
}