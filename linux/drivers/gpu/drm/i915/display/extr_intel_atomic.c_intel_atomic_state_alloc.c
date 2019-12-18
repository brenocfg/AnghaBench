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
struct drm_atomic_state {int dummy; } ;
struct intel_atomic_state {struct drm_atomic_state base; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ drm_atomic_state_init (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct intel_atomic_state*) ; 
 struct intel_atomic_state* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_atomic_state *
intel_atomic_state_alloc(struct drm_device *dev)
{
	struct intel_atomic_state *state = kzalloc(sizeof(*state), GFP_KERNEL);

	if (!state || drm_atomic_state_init(dev, &state->base) < 0) {
		kfree(state);
		return NULL;
	}

	return &state->base;
}