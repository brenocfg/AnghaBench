#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct msm_kms {int /*<<< orphan*/  aspace; } ;
struct TYPE_2__ {struct msm_kms base; } ;
struct mdp5_kms {TYPE_1__ base; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int MDP5_PIPE_SRC_STRIDE_A_P0 (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_SRC_STRIDE_A_P1 (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_SRC_STRIDE_B_P2 (int /*<<< orphan*/ ) ; 
 int MDP5_PIPE_SRC_STRIDE_B_P3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC0_ADDR (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC1_ADDR (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC2_ADDR (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC3_ADDR (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC_STRIDE_A (int) ; 
 int /*<<< orphan*/  REG_MDP5_PIPE_SRC_STRIDE_B (int) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int msm_framebuffer_iova (struct drm_framebuffer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_scanout_locked(struct mdp5_kms *mdp5_kms,
			       enum mdp5_pipe pipe,
			       struct drm_framebuffer *fb)
{
	struct msm_kms *kms = &mdp5_kms->base.base;

	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC_STRIDE_A(pipe),
			MDP5_PIPE_SRC_STRIDE_A_P0(fb->pitches[0]) |
			MDP5_PIPE_SRC_STRIDE_A_P1(fb->pitches[1]));

	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC_STRIDE_B(pipe),
			MDP5_PIPE_SRC_STRIDE_B_P2(fb->pitches[2]) |
			MDP5_PIPE_SRC_STRIDE_B_P3(fb->pitches[3]));

	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC0_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 0));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC1_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 1));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC2_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 2));
	mdp5_write(mdp5_kms, REG_MDP5_PIPE_SRC3_ADDR(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 3));
}