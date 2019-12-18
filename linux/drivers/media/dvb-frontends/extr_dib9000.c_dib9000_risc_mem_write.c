#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {int /*<<< orphan*/  mem_lock; int /*<<< orphan*/  fw_is_running; struct dib9000_fe_memory_map* fe_mm; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {TYPE_2__ platform; } ;
struct dib9000_fe_memory_map {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  dib9000_risc_mem_setup (struct dib9000_state*,size_t) ; 
 int /*<<< orphan*/  dib9000_risc_mem_write_chunks (struct dib9000_state*,size_t const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_risc_mem_write(struct dib9000_state *state, u8 cmd, const u8 * b)
{
	struct dib9000_fe_memory_map *m = &state->platform.risc.fe_mm[cmd];
	if (!state->platform.risc.fw_is_running)
		return -EIO;

	if (mutex_lock_interruptible(&state->platform.risc.mem_lock) < 0) {
		dprintk("could not get the lock\n");
		return -EINTR;
	}
	dib9000_risc_mem_setup(state, cmd);
	dib9000_risc_mem_write_chunks(state, b, m->size);
	mutex_unlock(&state->platform.risc.mem_lock);
	return 0;
}