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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_mbx_lock; } ;
struct TYPE_4__ {TYPE_1__ risc; } ;
struct dib9000_state {int /*<<< orphan*/  demod_lock; TYPE_2__ platform; scalar_t__ i2c_read_buffer; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int /*<<< orphan*/  FE_MM_R_FE_MONITOR ; 
 int /*<<< orphan*/  FE_SYNC_CHANNEL ; 
 scalar_t__ dib9000_fw_memmbx_sync (struct dib9000_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dib9000_risc_mem_read (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_read_unc_blocks(struct dvb_frontend *fe, u32 * unc)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u16 *c = (u16 *)state->i2c_read_buffer;
	int ret = 0;

	if (mutex_lock_interruptible(&state->demod_lock) < 0) {
		dprintk("could not get the lock\n");
		return -EINTR;
	}
	if (mutex_lock_interruptible(&state->platform.risc.mem_mbx_lock) < 0) {
		dprintk("could not get the lock\n");
		ret = -EINTR;
		goto error;
	}
	if (dib9000_fw_memmbx_sync(state, FE_SYNC_CHANNEL) < 0) {
		mutex_unlock(&state->platform.risc.mem_mbx_lock);
		ret = -EIO;
		goto error;
	}
	dib9000_risc_mem_read(state, FE_MM_R_FE_MONITOR, (u8 *) c, 16 * 2);
	mutex_unlock(&state->platform.risc.mem_mbx_lock);

	*unc = c[12];

error:
	mutex_unlock(&state->demod_lock);
	return ret;
}