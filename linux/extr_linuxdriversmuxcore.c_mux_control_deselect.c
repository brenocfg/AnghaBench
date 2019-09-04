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
struct mux_control {scalar_t__ idle_state; scalar_t__ cached_state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ MUX_IDLE_AS_IS ; 
 int mux_control_set (struct mux_control*,scalar_t__) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int mux_control_deselect(struct mux_control *mux)
{
	int ret = 0;

	if (mux->idle_state != MUX_IDLE_AS_IS &&
	    mux->idle_state != mux->cached_state)
		ret = mux_control_set(mux, mux->idle_state);

	up(&mux->lock);

	return ret;
}