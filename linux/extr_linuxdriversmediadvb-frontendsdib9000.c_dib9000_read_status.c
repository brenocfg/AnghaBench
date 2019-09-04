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
typedef  size_t u8 ;
typedef  int u16 ;
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {int /*<<< orphan*/  demod_lock; int /*<<< orphan*/ ** fe; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int EINTR ; 
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int dib9000_read_lock (int /*<<< orphan*/ *) ; 
 int dib9000_read_word (struct dib9000_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib9000_read_status(struct dvb_frontend *fe, enum fe_status *stat)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u8 index_frontend;
	u16 lock = 0, lock_slave = 0;

	if (mutex_lock_interruptible(&state->demod_lock) < 0) {
		dprintk("could not get the lock\n");
		return -EINTR;
	}
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++)
		lock_slave |= dib9000_read_lock(state->fe[index_frontend]);

	lock = dib9000_read_word(state, 535);

	*stat = 0;

	if ((lock & 0x8000) || (lock_slave & 0x8000))
		*stat |= FE_HAS_SIGNAL;
	if ((lock & 0x3000) || (lock_slave & 0x3000))
		*stat |= FE_HAS_CARRIER;
	if ((lock & 0x0100) || (lock_slave & 0x0100))
		*stat |= FE_HAS_VITERBI;
	if (((lock & 0x0038) == 0x38) || ((lock_slave & 0x0038) == 0x38))
		*stat |= FE_HAS_SYNC;
	if ((lock & 0x0008) || (lock_slave & 0x0008))
		*stat |= FE_HAS_LOCK;

	mutex_unlock(&state->demod_lock);

	return 0;
}