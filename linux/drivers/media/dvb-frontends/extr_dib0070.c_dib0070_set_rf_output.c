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
typedef  int u16 ;
struct dvb_frontend {struct dib0070_state* tuner_priv; } ;
struct dib0070_state {int dummy; } ;

/* Variables and functions */
 int dib0070_read_reg (struct dib0070_state*,int) ; 
 int dib0070_write_reg (struct dib0070_state*,int,int) ; 

int dib0070_set_rf_output(struct dvb_frontend *fe, u8 no)
{
	struct dib0070_state *state = fe->tuner_priv;
	u16 rxrf2 = dib0070_read_reg(state, 0x07) & 0xfe7ff;
	if (no > 3)
		no = 3;
	if (no < 1)
		no = 1;
	return dib0070_write_reg(state, 0x07, rxrf2 | (no << 11));
}