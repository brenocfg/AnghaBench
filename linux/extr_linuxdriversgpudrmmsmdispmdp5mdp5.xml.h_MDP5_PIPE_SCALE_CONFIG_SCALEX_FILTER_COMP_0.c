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
typedef  enum mdp5_scale_filter { ____Placeholder_mdp5_scale_filter } mdp5_scale_filter ;

/* Variables and functions */
 int MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0__MASK ; 
 int MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0__SHIFT ; 

__attribute__((used)) static inline uint32_t MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0(enum mdp5_scale_filter val)
{
	return ((val) << MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0__SHIFT) & MDP5_PIPE_SCALE_CONFIG_SCALEX_FILTER_COMP_0__MASK;
}