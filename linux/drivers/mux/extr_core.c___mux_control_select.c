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
struct mux_control {int states; int cached_state; int idle_state; } ;

/* Variables and functions */
 int EINVAL ; 
 int MUX_IDLE_AS_IS ; 
 scalar_t__ WARN_ON (int) ; 
 int mux_control_set (struct mux_control*,int) ; 

__attribute__((used)) static int __mux_control_select(struct mux_control *mux, int state)
{
	int ret;

	if (WARN_ON(state < 0 || state >= mux->states))
		return -EINVAL;

	if (mux->cached_state == state)
		return 0;

	ret = mux_control_set(mux, state);
	if (ret >= 0)
		return 0;

	/* The mux update failed, try to revert if appropriate... */
	if (mux->idle_state != MUX_IDLE_AS_IS)
		mux_control_set(mux, mux->idle_state);

	return ret;
}