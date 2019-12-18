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
typedef  enum pipe { ____Placeholder_pipe } pipe ;
typedef  enum dpio_channel { ____Placeholder_dpio_channel } dpio_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DPIO_CH0 ; 
 int DPIO_CH1 ; 
#define  PIPE_A 130 
#define  PIPE_B 129 
#define  PIPE_C 128 

__attribute__((used)) static inline enum dpio_channel
vlv_pipe_to_channel(enum pipe pipe)
{
	switch (pipe) {
	case PIPE_A:
	case PIPE_C:
		return DPIO_CH0;
	case PIPE_B:
		return DPIO_CH1;
	default:
		BUG();
	}
}