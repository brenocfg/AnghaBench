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
typedef  int uint32_t ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;

/* Variables and functions */
 int MDP_PIPE_CAP_CSC ; 
 int MDP_PIPE_CAP_HFLIP ; 
 int MDP_PIPE_CAP_SCALE ; 
 int MDP_PIPE_CAP_VFLIP ; 
#define  RGB1 134 
#define  RGB2 133 
#define  RGB3 132 
#define  VG1 131 
#define  VG2 130 
#define  VG3 129 
#define  VG4 128 

__attribute__((used)) static inline uint32_t mdp4_pipe_caps(enum mdp4_pipe pipe)
{
	switch (pipe) {
	case VG1:
	case VG2:
	case VG3:
	case VG4:
		return MDP_PIPE_CAP_HFLIP | MDP_PIPE_CAP_VFLIP |
				MDP_PIPE_CAP_SCALE | MDP_PIPE_CAP_CSC;
	case RGB1:
	case RGB2:
	case RGB3:
		return MDP_PIPE_CAP_SCALE;
	default:
		return 0;
	}
}