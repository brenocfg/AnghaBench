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
struct mdp5_kms {int /*<<< orphan*/  glob_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  glob_state_lock; } ;
struct mdp5_global_state {int /*<<< orphan*/  base; struct mdp5_kms* mdp5_kms; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_atomic_private_obj_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_init (int /*<<< orphan*/ *) ; 
 struct mdp5_global_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_global_state_funcs ; 

__attribute__((used)) static int mdp5_global_obj_init(struct mdp5_kms *mdp5_kms)
{
	struct mdp5_global_state *state;

	drm_modeset_lock_init(&mdp5_kms->glob_state_lock);

	state = kzalloc(sizeof(*state), GFP_KERNEL);
	if (!state)
		return -ENOMEM;

	state->mdp5_kms = mdp5_kms;

	drm_atomic_private_obj_init(mdp5_kms->dev, &mdp5_kms->glob_state,
				    &state->base,
				    &mdp5_global_state_funcs);
	return 0;
}