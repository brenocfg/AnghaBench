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
struct mdp4_plane {int pipe; } ;
struct TYPE_2__ {struct msm_kms base; } ;
struct mdp4_kms {TYPE_1__ base; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; } ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;

/* Variables and functions */
 int MDP4_PIPE_SRC_STRIDE_A_P0 (int /*<<< orphan*/ ) ; 
 int MDP4_PIPE_SRC_STRIDE_A_P1 (int /*<<< orphan*/ ) ; 
 int MDP4_PIPE_SRC_STRIDE_B_P2 (int /*<<< orphan*/ ) ; 
 int MDP4_PIPE_SRC_STRIDE_B_P3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRCP0_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRCP1_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRCP2_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRCP3_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRC_STRIDE_A (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_SRC_STRIDE_B (int) ; 
 struct mdp4_kms* get_kms (struct drm_plane*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 int msm_framebuffer_iova (struct drm_framebuffer*,int /*<<< orphan*/ ,int) ; 
 struct mdp4_plane* to_mdp4_plane (struct drm_plane*) ; 

__attribute__((used)) static void mdp4_plane_set_scanout(struct drm_plane *plane,
		struct drm_framebuffer *fb)
{
	struct mdp4_plane *mdp4_plane = to_mdp4_plane(plane);
	struct mdp4_kms *mdp4_kms = get_kms(plane);
	struct msm_kms *kms = &mdp4_kms->base.base;
	enum mdp4_pipe pipe = mdp4_plane->pipe;

	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRC_STRIDE_A(pipe),
			MDP4_PIPE_SRC_STRIDE_A_P0(fb->pitches[0]) |
			MDP4_PIPE_SRC_STRIDE_A_P1(fb->pitches[1]));

	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRC_STRIDE_B(pipe),
			MDP4_PIPE_SRC_STRIDE_B_P2(fb->pitches[2]) |
			MDP4_PIPE_SRC_STRIDE_B_P3(fb->pitches[3]));

	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRCP0_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 0));
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRCP1_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 1));
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRCP2_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 2));
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_SRCP3_BASE(pipe),
			msm_framebuffer_iova(fb, kms->aspace, 3));
}