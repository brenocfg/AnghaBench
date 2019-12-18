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
struct dvb_frontend {struct dib7000p_state* demodulator_priv; } ;
struct dib7000p_state {int dummy; } ;

/* Variables and functions */
 int dib7000p_read_word (struct dib7000p_state*,int) ; 
 int dib7000p_write_word (struct dib7000p_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int dib7000p_pid_filter_ctrl(struct dvb_frontend *fe, u8 onoff)
{
	struct dib7000p_state *state = fe->demodulator_priv;
	u16 val = dib7000p_read_word(state, 235) & 0xffef;
	val |= (onoff & 0x1) << 4;
	dprintk("PID filter enabled %d\n", onoff);
	return dib7000p_write_word(state, 235, val);
}