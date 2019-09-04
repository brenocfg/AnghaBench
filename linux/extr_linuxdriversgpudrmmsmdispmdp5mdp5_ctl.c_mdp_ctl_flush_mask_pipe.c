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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int /*<<< orphan*/  MDP5_CTL_FLUSH_CURSOR_0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_CURSOR_1 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_DMA0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_DMA1 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_RGB0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_RGB1 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_RGB2 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_RGB3 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_VIG0 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_VIG1 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_VIG2 ; 
 int /*<<< orphan*/  MDP5_CTL_FLUSH_VIG3 ; 
#define  SSPP_CURSOR0 139 
#define  SSPP_CURSOR1 138 
#define  SSPP_DMA0 137 
#define  SSPP_DMA1 136 
#define  SSPP_RGB0 135 
#define  SSPP_RGB1 134 
#define  SSPP_RGB2 133 
#define  SSPP_RGB3 132 
#define  SSPP_VIG0 131 
#define  SSPP_VIG1 130 
#define  SSPP_VIG2 129 
#define  SSPP_VIG3 128 

u32 mdp_ctl_flush_mask_pipe(enum mdp5_pipe pipe)
{
	switch (pipe) {
	case SSPP_VIG0: return MDP5_CTL_FLUSH_VIG0;
	case SSPP_VIG1: return MDP5_CTL_FLUSH_VIG1;
	case SSPP_VIG2: return MDP5_CTL_FLUSH_VIG2;
	case SSPP_RGB0: return MDP5_CTL_FLUSH_RGB0;
	case SSPP_RGB1: return MDP5_CTL_FLUSH_RGB1;
	case SSPP_RGB2: return MDP5_CTL_FLUSH_RGB2;
	case SSPP_DMA0: return MDP5_CTL_FLUSH_DMA0;
	case SSPP_DMA1: return MDP5_CTL_FLUSH_DMA1;
	case SSPP_VIG3: return MDP5_CTL_FLUSH_VIG3;
	case SSPP_RGB3: return MDP5_CTL_FLUSH_RGB3;
	case SSPP_CURSOR0: return MDP5_CTL_FLUSH_CURSOR_0;
	case SSPP_CURSOR1: return MDP5_CTL_FLUSH_CURSOR_1;
	default:        return 0;
	}
}