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
struct mdp4_kms {int dummy; } ;
struct csc_cfg {int /*<<< orphan*/ * post_clamp; int /*<<< orphan*/ * pre_clamp; int /*<<< orphan*/ * post_bias; int /*<<< orphan*/ * pre_bias; int /*<<< orphan*/ * matrix; } ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_CSC_MV (int,int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_CSC_POST_BV (int,int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_CSC_POST_LV (int,int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_CSC_PRE_BV (int,int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_CSC_PRE_LV (int,int) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp4_write_csc_config(struct mdp4_kms *mdp4_kms,
		enum mdp4_pipe pipe, struct csc_cfg *csc)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(csc->matrix); i++) {
		mdp4_write(mdp4_kms, REG_MDP4_PIPE_CSC_MV(pipe, i),
				csc->matrix[i]);
	}

	for (i = 0; i < ARRAY_SIZE(csc->post_bias) ; i++) {
		mdp4_write(mdp4_kms, REG_MDP4_PIPE_CSC_PRE_BV(pipe, i),
				csc->pre_bias[i]);

		mdp4_write(mdp4_kms, REG_MDP4_PIPE_CSC_POST_BV(pipe, i),
				csc->post_bias[i]);
	}

	for (i = 0; i < ARRAY_SIZE(csc->post_clamp) ; i++) {
		mdp4_write(mdp4_kms, REG_MDP4_PIPE_CSC_PRE_LV(pipe, i),
				csc->pre_clamp[i]);

		mdp4_write(mdp4_kms, REG_MDP4_PIPE_CSC_POST_LV(pipe, i),
				csc->post_clamp[i]);
	}
}