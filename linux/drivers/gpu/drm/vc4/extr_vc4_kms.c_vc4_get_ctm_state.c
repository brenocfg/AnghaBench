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
struct vc4_dev {int /*<<< orphan*/  ctm_state_lock; } ;
struct vc4_ctm_state {int dummy; } ;
struct drm_private_state {int dummy; } ;
struct drm_private_obj {int dummy; } ;
struct drm_device {struct vc4_dev* dev_private; } ;
struct drm_atomic_state {int /*<<< orphan*/  acquire_ctx; struct drm_device* dev; } ;

/* Variables and functions */
 struct vc4_ctm_state* ERR_CAST (struct drm_private_state*) ; 
 struct vc4_ctm_state* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct drm_private_state*) ; 
 struct drm_private_state* drm_atomic_get_private_obj_state (struct drm_atomic_state*,struct drm_private_obj*) ; 
 int drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vc4_ctm_state* to_vc4_ctm_state (struct drm_private_state*) ; 

__attribute__((used)) static struct vc4_ctm_state *vc4_get_ctm_state(struct drm_atomic_state *state,
					       struct drm_private_obj *manager)
{
	struct drm_device *dev = state->dev;
	struct vc4_dev *vc4 = dev->dev_private;
	struct drm_private_state *priv_state;
	int ret;

	ret = drm_modeset_lock(&vc4->ctm_state_lock, state->acquire_ctx);
	if (ret)
		return ERR_PTR(ret);

	priv_state = drm_atomic_get_private_obj_state(state, manager);
	if (IS_ERR(priv_state))
		return ERR_CAST(priv_state);

	return to_vc4_ctm_state(priv_state);
}