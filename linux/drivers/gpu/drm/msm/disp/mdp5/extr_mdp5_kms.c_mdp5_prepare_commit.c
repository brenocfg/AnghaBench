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
struct msm_kms {int dummy; } ;
struct mdp5_kms {scalar_t__ smp; } ;
struct mdp5_global_state {int /*<<< orphan*/  smp; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct mdp5_global_state* mdp5_get_existing_global_state (struct mdp5_kms*) ; 
 int /*<<< orphan*/  mdp5_smp_prepare_commit (scalar_t__,int /*<<< orphan*/ *) ; 
 struct mdp5_kms* to_mdp5_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

__attribute__((used)) static void mdp5_prepare_commit(struct msm_kms *kms, struct drm_atomic_state *state)
{
	struct mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	struct mdp5_global_state *global_state;

	global_state = mdp5_get_existing_global_state(mdp5_kms);

	if (mdp5_kms->smp)
		mdp5_smp_prepare_commit(mdp5_kms->smp, &global_state->smp);
}