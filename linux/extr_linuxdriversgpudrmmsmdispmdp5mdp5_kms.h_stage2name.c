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
typedef  enum mdp_mixer_stage_id { ____Placeholder_mdp_mixer_stage_id } mdp_mixer_stage_id ;

/* Variables and functions */
#define  STAGE0 135 
#define  STAGE1 134 
#define  STAGE2 133 
#define  STAGE3 132 
#define  STAGE4 131 
#define  STAGE6 130 
#define  STAGE_BASE 129 
#define  STAGE_UNUSED 128 

__attribute__((used)) static inline const char *stage2name(enum mdp_mixer_stage_id stage)
{
	static const char *names[] = {
#define NAME(n) [n] = #n
		NAME(STAGE_UNUSED), NAME(STAGE_BASE),
		NAME(STAGE0), NAME(STAGE1), NAME(STAGE2),
		NAME(STAGE3), NAME(STAGE4), NAME(STAGE6),
#undef NAME
	};
	return names[stage];
}