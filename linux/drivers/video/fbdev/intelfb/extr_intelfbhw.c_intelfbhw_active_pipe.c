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
struct intelfb_hwstate {int disp_b_ctrl; int disp_a_ctrl; } ;

/* Variables and functions */
 int DISPPLANE_PLANE_ENABLE ; 
 int DISPPLANE_SEL_PIPE_SHIFT ; 
 int PIPE_A ; 
 int PIPE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

int intelfbhw_active_pipe(const struct intelfb_hwstate *hw)
{
	int pipe = -1;

	/* keep old default behaviour - prefer PIPE_A */
	if (hw->disp_b_ctrl & DISPPLANE_PLANE_ENABLE) {
		pipe = (hw->disp_b_ctrl >> DISPPLANE_SEL_PIPE_SHIFT);
		pipe &= PIPE_MASK;
		if (unlikely(pipe == PIPE_A))
			return PIPE_A;
	}
	if (hw->disp_a_ctrl & DISPPLANE_PLANE_ENABLE) {
		pipe = (hw->disp_a_ctrl >> DISPPLANE_SEL_PIPE_SHIFT);
		pipe &= PIPE_MASK;
		if (likely(pipe == PIPE_A))
			return PIPE_A;
	}
	/* Impossible that no pipe is selected - return PIPE_A */
	WARN_ON(pipe == -1);
	if (unlikely(pipe == -1))
		pipe = PIPE_A;

	return pipe;
}