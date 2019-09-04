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
typedef  enum mdp4_scale_unit { ____Placeholder_mdp4_scale_unit } mdp4_scale_unit ;

/* Variables and functions */
 int MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL__MASK ; 
 int MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL(enum mdp4_scale_unit val)
{
	return ((val) << MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL__SHIFT) & MDP4_PIPE_OP_MODE_SCALEY_UNIT_SEL__MASK;
}