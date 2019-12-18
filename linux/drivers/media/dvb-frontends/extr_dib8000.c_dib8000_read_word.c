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
typedef  int /*<<< orphan*/  u16 ;
struct dib8000_state {int /*<<< orphan*/  i2c_buffer_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dib8000_read_word (struct dib8000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 dib8000_read_word(struct dib8000_state *state, u16 reg)
{
	u16 ret;

	if (mutex_lock_interruptible(&state->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return 0;
	}

	ret = __dib8000_read_word(state, reg);

	mutex_unlock(&state->i2c_buffer_lock);

	return ret;
}