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
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;

/* Variables and functions */
 int __offset_PIPE (int) ; 

__attribute__((used)) static inline uint32_t REG_MDP5_PIPE_CSC_1_POST_CLAMP(enum mdp5_pipe i0, uint32_t i1) { return 0x00000340 + __offset_PIPE(i0) + 0x4*i1; }