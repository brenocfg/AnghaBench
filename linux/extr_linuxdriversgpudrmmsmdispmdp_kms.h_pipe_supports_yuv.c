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

/* Variables and functions */
 int MDP_PIPE_CAP_CSC ; 
 int MDP_PIPE_CAP_SCALE ; 

__attribute__((used)) static inline bool pipe_supports_yuv(uint32_t pipe_caps)
{
	return (pipe_caps & MDP_PIPE_CAP_SCALE) &&
		(pipe_caps & MDP_PIPE_CAP_CSC);
}