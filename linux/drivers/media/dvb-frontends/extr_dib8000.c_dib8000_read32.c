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
typedef  int u32 ;
typedef  int u16 ;
struct dib8000_state {int /*<<< orphan*/  i2c_buffer_lock; } ;

/* Variables and functions */
 int __dib8000_read_word (struct dib8000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 dib8000_read32(struct dib8000_state *state, u16 reg)
{
	u16 rw[2];

	if (mutex_lock_interruptible(&state->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return 0;
	}

	rw[0] = __dib8000_read_word(state, reg + 0);
	rw[1] = __dib8000_read_word(state, reg + 1);

	mutex_unlock(&state->i2c_buffer_lock);

	return ((rw[0] << 16) | (rw[1]));
}