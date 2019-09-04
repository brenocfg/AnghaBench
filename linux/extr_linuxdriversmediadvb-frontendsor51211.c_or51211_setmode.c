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
typedef  int u8 ;
struct or51211_state {TYPE_1__* config; } ;
struct dvb_frontend {struct or51211_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  demod_address; int /*<<< orphan*/  (* setmode ) (struct dvb_frontend*,int) ;} ;

/* Variables and functions */
 int* cmd_buf ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 scalar_t__ i2c_readbytes (struct or51211_state*,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ i2c_writebytes (struct or51211_state*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* run_buf ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int or51211_setmode(struct dvb_frontend* fe, int mode)
{
	struct or51211_state* state = fe->demodulator_priv;
	u8 rec_buf[14];

	state->config->setmode(fe, mode);

	if (i2c_writebytes(state,state->config->demod_address,run_buf,2)) {
		pr_warn("error 1\n");
		return -1;
	}

	/* Wait at least 5 msec */
	msleep(10);
	if (i2c_writebytes(state,state->config->demod_address,run_buf,2)) {
		pr_warn("error 2\n");
		return -1;
	}

	msleep(10);

	/* Set operation mode in Receiver 1 register;
	 * type 1:
	 * data 0x50h  Automatic sets receiver channel conditions
	 *             Automatic NTSC rejection filter
	 *             Enable  MPEG serial data output
	 *             MPEG2tr
	 *             High tuner phase noise
	 *             normal +/-150kHz Carrier acquisition range
	 */
	if (i2c_writebytes(state,state->config->demod_address,cmd_buf,3)) {
		pr_warn("error 3\n");
		return -1;
	}

	rec_buf[0] = 0x04;
	rec_buf[1] = 0x00;
	rec_buf[2] = 0x03;
	rec_buf[3] = 0x00;
	msleep(20);
	if (i2c_writebytes(state,state->config->demod_address,rec_buf,3)) {
		pr_warn("error 5\n");
	}
	msleep(3);
	if (i2c_readbytes(state,state->config->demod_address,&rec_buf[10],2)) {
		pr_warn("error 6\n");
		return -1;
	}
	dprintk("rec status %02x %02x\n", rec_buf[10], rec_buf[11]);

	return 0;
}