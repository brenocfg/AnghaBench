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
struct drm_device {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct dm_atomic_state {struct drm_atomic_state base; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ drm_atomic_state_init (struct drm_device*,struct drm_atomic_state*) ; 
 int /*<<< orphan*/  kfree (struct dm_atomic_state*) ; 
 struct dm_atomic_state* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_atomic_state *
dm_atomic_state_alloc(struct drm_device *dev)
{
	struct dm_atomic_state *state = kzalloc(sizeof(*state), GFP_KERNEL);

	if (!state)
		return NULL;

	if (drm_atomic_state_init(dev, &state->base) < 0)
		goto fail;

	return &state->base;

fail:
	kfree(state);
	return NULL;
}