#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct or51211_state {TYPE_1__* config; } ;
struct dvb_frontend {struct or51211_state* demodulator_priv; } ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; } ;

/* Variables and functions */
 int FE_HAS_CARRIER ; 
 int FE_HAS_LOCK ; 
 int FE_HAS_SIGNAL ; 
 int FE_HAS_SYNC ; 
 int FE_HAS_VITERBI ; 
 int /*<<< orphan*/  dprintk (char*,unsigned char,unsigned char) ; 
 scalar_t__ i2c_readbytes (struct or51211_state*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ i2c_writebytes (struct or51211_state*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int or51211_read_status(struct dvb_frontend *fe, enum fe_status *status)
{
	struct or51211_state* state = fe->demodulator_priv;
	unsigned char rec_buf[2];
	unsigned char snd_buf[] = {0x04,0x00,0x03,0x00};
	*status = 0;

	/* Receiver Status */
	if (i2c_writebytes(state,state->config->demod_address,snd_buf,3)) {
		pr_warn("write error\n");
		return -1;
	}
	msleep(3);
	if (i2c_readbytes(state,state->config->demod_address,rec_buf,2)) {
		pr_warn("read error\n");
		return -1;
	}
	dprintk("%x %x\n", rec_buf[0], rec_buf[1]);

	if (rec_buf[0] &  0x01) { /* Receiver Lock */
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	}
	return 0;
}