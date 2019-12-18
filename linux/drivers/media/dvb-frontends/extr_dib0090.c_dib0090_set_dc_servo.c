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
typedef  int u8 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 

void dib0090_set_dc_servo(struct dvb_frontend *fe, u8 DC_servo_cutoff)
{
	struct dib0090_state *state = fe->tuner_priv;
	if (DC_servo_cutoff < 4)
		dib0090_write_reg(state, 0x04, DC_servo_cutoff);
}