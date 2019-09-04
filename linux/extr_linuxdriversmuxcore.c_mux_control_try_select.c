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
struct mux_control {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int __mux_control_select (struct mux_control*,unsigned int) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int mux_control_try_select(struct mux_control *mux, unsigned int state)
{
	int ret;

	if (down_trylock(&mux->lock))
		return -EBUSY;

	ret = __mux_control_select(mux, state);

	if (ret < 0)
		up(&mux->lock);

	return ret;
}