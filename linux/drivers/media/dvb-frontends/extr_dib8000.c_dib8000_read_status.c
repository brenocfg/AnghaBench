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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {struct dvb_frontend** fe; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int /*<<< orphan*/  dib8000_get_stats (struct dvb_frontend*,int) ; 
 int dib8000_read_lock (struct dvb_frontend*) ; 
 int dib8000_read_word (struct dib8000_state*,int) ; 

__attribute__((used)) static int dib8000_read_status(struct dvb_frontend *fe, enum fe_status *stat)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 lock_slave = 0, lock;
	u8 index_frontend;

	lock = dib8000_read_lock(fe);
	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (state->fe[index_frontend] != NULL); index_frontend++)
		lock_slave |= dib8000_read_lock(state->fe[index_frontend]);

	*stat = 0;

	if (((lock >> 13) & 1) || ((lock_slave >> 13) & 1))
		*stat |= FE_HAS_SIGNAL;

	if (((lock >> 8) & 1) || ((lock_slave >> 8) & 1)) /* Equal */
		*stat |= FE_HAS_CARRIER;

	if ((((lock >> 1) & 0xf) == 0xf) || (((lock_slave >> 1) & 0xf) == 0xf)) /* TMCC_SYNC */
		*stat |= FE_HAS_SYNC;

	if ((((lock >> 12) & 1) || ((lock_slave >> 12) & 1)) && ((lock >> 5) & 7)) /* FEC MPEG */
		*stat |= FE_HAS_LOCK;

	if (((lock >> 12) & 1) || ((lock_slave >> 12) & 1)) {
		lock = dib8000_read_word(state, 554); /* Viterbi Layer A */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_read_word(state, 555); /* Viterbi Layer B */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;

		lock = dib8000_read_word(state, 556); /* Viterbi Layer C */
		if (lock & 0x01)
			*stat |= FE_HAS_VITERBI;
	}
	dib8000_get_stats(fe, *stat);

	return 0;
}