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
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int dib8000_write_word (struct dib8000_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int dib8000_pid_filter_ctrl(struct dvb_frontend *fe, u8 onoff)
{
	struct dib8000_state *st = fe->demodulator_priv;
	u16 val = dib8000_read_word(st, 299) & 0xffef;
	val |= (onoff & 0x1) << 4;

	dprintk("pid filter enabled %d\n", onoff);
	return dib8000_write_word(st, 299, val);
}