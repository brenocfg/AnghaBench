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
struct intel_bw_state {int /*<<< orphan*/  base; } ;
struct drm_i915_private {int /*<<< orphan*/  bw_obj; int /*<<< orphan*/  drm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_bw_funcs ; 
 struct intel_bw_state* kzalloc (int,int /*<<< orphan*/ ) ; 

int intel_bw_init(struct drm_i915_private *dev_priv)
{
	struct intel_bw_state *state;

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	drm_atomic_private_obj_init(&dev_priv->drm, &dev_priv->bw_obj,
				    &state->base, &intel_bw_funcs);

	return 0;
}