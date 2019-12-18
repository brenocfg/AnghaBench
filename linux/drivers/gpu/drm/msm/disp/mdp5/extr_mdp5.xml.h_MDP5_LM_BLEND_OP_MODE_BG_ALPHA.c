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
typedef  enum mdp_alpha_type { ____Placeholder_mdp_alpha_type } mdp_alpha_type ;

/* Variables and functions */
 int MDP5_LM_BLEND_OP_MODE_BG_ALPHA__MASK ; 
 int MDP5_LM_BLEND_OP_MODE_BG_ALPHA__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP5_LM_BLEND_OP_MODE_BG_ALPHA(enum mdp_alpha_type val)
{
	return ((val) << MDP5_LM_BLEND_OP_MODE_BG_ALPHA__SHIFT) & MDP5_LM_BLEND_OP_MODE_BG_ALPHA__MASK;
}