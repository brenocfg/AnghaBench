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
struct ipw_hardware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIO_CTRL ; 
 int set_DTR (struct ipw_hardware*,int /*<<< orphan*/ ,unsigned int,int) ; 

int ipwireless_set_DTR(struct ipw_hardware *hw, unsigned int channel_idx,
		       int state)
{
	return set_DTR(hw, PRIO_CTRL, channel_idx, state);
}