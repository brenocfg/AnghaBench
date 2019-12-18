#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ inversion; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_if_frequency ) (struct dvb_frontend*,int*) ;} ;
struct TYPE_7__ {TYPE_2__ tuner_ops; } ;
struct dvb_frontend {TYPE_3__ ops; } ;
struct si2165_state {TYPE_4__ config; TYPE_1__* client; struct dvb_frontend fe; } ;
typedef  int s32 ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  REG_IF_FREQ_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int si2165_get_fe_clk (struct si2165_state*) ; 
 int si2165_writereg32 (struct si2165_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int si2165_set_if_freq_shift(struct si2165_state *state)
{
	struct dvb_frontend *fe = &state->fe;
	u64 if_freq_shift;
	s32 reg_value = 0;
	u32 fe_clk = si2165_get_fe_clk(state);
	u32 IF = 0;

	if (!fe->ops.tuner_ops.get_if_frequency) {
		dev_err(&state->client->dev,
			"Error: get_if_frequency() not defined at tuner. Can't work without it!\n");
		return -EINVAL;
	}

	if (!fe_clk)
		return -EINVAL;

	fe->ops.tuner_ops.get_if_frequency(fe, &IF);
	if_freq_shift = IF;
	if_freq_shift <<= 29;

	do_div(if_freq_shift, fe_clk);
	reg_value = (s32)if_freq_shift;

	if (state->config.inversion)
		reg_value = -reg_value;

	reg_value = reg_value & 0x1fffffff;

	/* if_freq_shift, usbdump contained 0x023ee08f; */
	return si2165_writereg32(state, REG_IF_FREQ_SHIFT, reg_value);
}