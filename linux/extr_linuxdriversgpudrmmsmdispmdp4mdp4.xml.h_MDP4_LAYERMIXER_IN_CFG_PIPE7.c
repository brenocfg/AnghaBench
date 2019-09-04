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
typedef  enum mdp_mixer_stage_id { ____Placeholder_mdp_mixer_stage_id } mdp_mixer_stage_id ;

/* Variables and functions */
 int MDP4_LAYERMIXER_IN_CFG_PIPE7__MASK ; 
 int MDP4_LAYERMIXER_IN_CFG_PIPE7__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP4_LAYERMIXER_IN_CFG_PIPE7(enum mdp_mixer_stage_id val)
{
	return ((val) << MDP4_LAYERMIXER_IN_CFG_PIPE7__SHIFT) & MDP4_LAYERMIXER_IN_CFG_PIPE7__MASK;
}