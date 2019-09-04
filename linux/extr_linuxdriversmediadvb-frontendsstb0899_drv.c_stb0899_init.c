#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stb0899_state {int /*<<< orphan*/  verbose; struct stb0899_config* config; } ;
struct stb0899_config {TYPE_5__* init_tst; TYPE_4__* init_s2_fec; TYPE_3__* init_s1_demod; TYPE_2__* init_s2_demod; TYPE_1__* init_dev; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
struct TYPE_10__ {int address; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int offset; int /*<<< orphan*/  data; int /*<<< orphan*/  base_address; } ;
struct TYPE_8__ {int address; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int offset; int /*<<< orphan*/  data; int /*<<< orphan*/  base_address; } ;
struct TYPE_6__ {int address; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  STB0899_S2DEMOD ; 
 int /*<<< orphan*/  STB0899_S2FEC ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stb0899_diseqc_init (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_init_calc (struct stb0899_state*) ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stb0899_write_s2reg (struct stb0899_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stb0899_init(struct dvb_frontend *fe)
{
	int i;
	struct stb0899_state *state = fe->demodulator_priv;
	struct stb0899_config *config = state->config;

	dprintk(state->verbose, FE_DEBUG, 1, "Initializing STB0899 ... ");

	/* init device		*/
	dprintk(state->verbose, FE_DEBUG, 1, "init device");
	for (i = 0; config->init_dev[i].address != 0xffff; i++)
		stb0899_write_reg(state, config->init_dev[i].address, config->init_dev[i].data);

	dprintk(state->verbose, FE_DEBUG, 1, "init S2 demod");
	/* init S2 demod	*/
	for (i = 0; config->init_s2_demod[i].offset != 0xffff; i++)
		stb0899_write_s2reg(state, STB0899_S2DEMOD,
				    config->init_s2_demod[i].base_address,
				    config->init_s2_demod[i].offset,
				    config->init_s2_demod[i].data);

	dprintk(state->verbose, FE_DEBUG, 1, "init S1 demod");
	/* init S1 demod	*/
	for (i = 0; config->init_s1_demod[i].address != 0xffff; i++)
		stb0899_write_reg(state, config->init_s1_demod[i].address, config->init_s1_demod[i].data);

	dprintk(state->verbose, FE_DEBUG, 1, "init S2 FEC");
	/* init S2 fec		*/
	for (i = 0; config->init_s2_fec[i].offset != 0xffff; i++)
		stb0899_write_s2reg(state, STB0899_S2FEC,
				    config->init_s2_fec[i].base_address,
				    config->init_s2_fec[i].offset,
				    config->init_s2_fec[i].data);

	dprintk(state->verbose, FE_DEBUG, 1, "init TST");
	/* init test		*/
	for (i = 0; config->init_tst[i].address != 0xffff; i++)
		stb0899_write_reg(state, config->init_tst[i].address, config->init_tst[i].data);

	stb0899_init_calc(state);
	stb0899_diseqc_init(state);

	return 0;
}