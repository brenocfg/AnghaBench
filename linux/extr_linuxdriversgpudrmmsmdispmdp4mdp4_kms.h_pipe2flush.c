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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum mdp4_pipe { ____Placeholder_mdp4_pipe } mdp4_pipe ;

/* Variables and functions */
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_RGB1 ; 
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_RGB2 ; 
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_VG1 ; 
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_VG2 ; 
#define  RGB1 131 
#define  RGB2 130 
#define  VG1 129 
#define  VG2 128 

__attribute__((used)) static inline uint32_t pipe2flush(enum mdp4_pipe pipe)
{
	switch (pipe) {
	case VG1:      return MDP4_OVERLAY_FLUSH_VG1;
	case VG2:      return MDP4_OVERLAY_FLUSH_VG2;
	case RGB1:     return MDP4_OVERLAY_FLUSH_RGB1;
	case RGB2:     return MDP4_OVERLAY_FLUSH_RGB2;
	default:       return 0;
	}
}