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
typedef  size_t u32 ;
struct mdp5_smp_state {void* state; void** client_state; } ;
struct mdp5_smp {int blk_cnt; } ;
struct mdp5_kms {int num_hwpipes; int /*<<< orphan*/  glob_state_lock; struct mdp5_hw_pipe** hwpipes; } ;
struct mdp5_hw_pipe_state {struct drm_plane** hwpipe_to_plane; } ;
struct mdp5_hw_pipe {size_t idx; int pipe; } ;
struct mdp5_global_state {struct mdp5_smp_state smp; struct mdp5_hw_pipe_state hwpipe; } ;
struct drm_printer {int dummy; } ;
struct drm_plane {int /*<<< orphan*/ * name; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int bitmap_weight (void*,int) ; 
 scalar_t__ drm_can_sleep () ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,...) ; 
 struct mdp5_kms* get_kms (struct mdp5_smp*) ; 
 struct mdp5_global_state* mdp5_get_existing_global_state (struct mdp5_kms*) ; 
 size_t pipe2client (int,int) ; 
 int /*<<< orphan*/  pipe2name (int) ; 
 int pipe2nclients (int) ; 

void mdp5_smp_dump(struct mdp5_smp *smp, struct drm_printer *p)
{
	struct mdp5_kms *mdp5_kms = get_kms(smp);
	struct mdp5_hw_pipe_state *hwpstate;
	struct mdp5_smp_state *state;
	struct mdp5_global_state *global_state;
	int total = 0, i, j;

	drm_printf(p, "name\tinuse\tplane\n");
	drm_printf(p, "----\t-----\t-----\n");

	if (drm_can_sleep())
		drm_modeset_lock(&mdp5_kms->glob_state_lock, NULL);

	global_state = mdp5_get_existing_global_state(mdp5_kms);

	/* grab these *after* we hold the state_lock */
	hwpstate = &global_state->hwpipe;
	state = &global_state->smp;

	for (i = 0; i < mdp5_kms->num_hwpipes; i++) {
		struct mdp5_hw_pipe *hwpipe = mdp5_kms->hwpipes[i];
		struct drm_plane *plane = hwpstate->hwpipe_to_plane[hwpipe->idx];
		enum mdp5_pipe pipe = hwpipe->pipe;
		for (j = 0; j < pipe2nclients(pipe); j++) {
			u32 cid = pipe2client(pipe, j);
			void *cs = state->client_state[cid];
			int inuse = bitmap_weight(cs, smp->blk_cnt);

			drm_printf(p, "%s:%d\t%d\t%s\n",
				pipe2name(pipe), j, inuse,
				plane ? plane->name : NULL);

			total += inuse;
		}
	}

	drm_printf(p, "TOTAL:\t%d\t(of %d)\n", total, smp->blk_cnt);
	drm_printf(p, "AVAIL:\t%d\n", smp->blk_cnt -
			bitmap_weight(state->state, smp->blk_cnt));

	if (drm_can_sleep())
		drm_modeset_unlock(&mdp5_kms->glob_state_lock);
}