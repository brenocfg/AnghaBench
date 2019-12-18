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
struct ipw_hardware {int /*<<< orphan*/ * control_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMCTRL_RTS ; 
 int /*<<< orphan*/  IPW_CONTROL_LINE_RTS ; 
 int set_control_line (struct ipw_hardware*,int,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_RTS(struct ipw_hardware *hw, int priority,
		   unsigned int channel_idx, int state)
{
	if (state != 0)
		hw->control_lines[channel_idx] |= IPW_CONTROL_LINE_RTS;
	else
		hw->control_lines[channel_idx] &= ~IPW_CONTROL_LINE_RTS;

	return set_control_line(hw, priority, channel_idx, COMCTRL_RTS, state);
}