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
struct firmware {int* data; int /*<<< orphan*/  size; } ;
struct dvb_frontend {struct or51211_state* demodulator_priv; } ;
struct TYPE_2__ {int demod_address; int /*<<< orphan*/  (* reset ) (struct dvb_frontend*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_readbytes (struct or51211_state*,int,int*,int) ; 
 scalar_t__ i2c_writebytes (struct or51211_state*,int,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int* run_buf ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*) ; 

__attribute__((used)) static int or51211_load_firmware (struct dvb_frontend* fe,
				  const struct firmware *fw)
{
	struct or51211_state* state = fe->demodulator_priv;
	u8 tudata[585];
	int i;

	dprintk("Firmware is %zu bytes\n", fw->size);

	/* Get eprom data */
	tudata[0] = 17;
	if (i2c_writebytes(state,0x50,tudata,1)) {
		pr_warn("error eprom addr\n");
		return -1;
	}
	if (i2c_readbytes(state,0x50,&tudata[145],192)) {
		pr_warn("error eprom\n");
		return -1;
	}

	/* Create firmware buffer */
	for (i = 0; i < 145; i++)
		tudata[i] = fw->data[i];

	for (i = 0; i < 248; i++)
		tudata[i+337] = fw->data[145+i];

	state->config->reset(fe);

	if (i2c_writebytes(state,state->config->demod_address,tudata,585)) {
		pr_warn("error 1\n");
		return -1;
	}
	msleep(1);

	if (i2c_writebytes(state,state->config->demod_address,
			   &fw->data[393],8125)) {
		pr_warn("error 2\n");
		return -1;
	}
	msleep(1);

	if (i2c_writebytes(state,state->config->demod_address,run_buf,2)) {
		pr_warn("error 3\n");
		return -1;
	}

	/* Wait at least 5 msec */
	msleep(10);
	if (i2c_writebytes(state,state->config->demod_address,run_buf,2)) {
		pr_warn("error 4\n");
		return -1;
	}
	msleep(10);

	pr_info("Done.\n");
	return 0;
}