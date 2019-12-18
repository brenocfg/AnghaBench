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
struct dvb_frontend {struct cx22702_state* demodulator_priv; } ;
struct cx22702_state {TYPE_1__* config; } ;
struct TYPE_2__ {int output_mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  cx22702_i2c_gate_ctrl (struct dvb_frontend*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx22702_writereg (struct cx22702_state*,int,int) ; 
 int* init_tab ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int cx22702_init(struct dvb_frontend *fe)
{
	int i;
	struct cx22702_state *state = fe->demodulator_priv;

	cx22702_writereg(state, 0x00, 0x02);

	msleep(10);

	for (i = 0; i < ARRAY_SIZE(init_tab); i += 2)
		cx22702_writereg(state, init_tab[i], init_tab[i + 1]);

	cx22702_writereg(state, 0xf8, (state->config->output_mode << 1)
		& 0x02);

	cx22702_i2c_gate_ctrl(fe, 0);

	return 0;
}