#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_wbd_slope {int max_freq; int wbd_gain; int offset_hot; int offset_cold; scalar_t__ slope_cold; scalar_t__ slope_hot; } ;
struct dib0090_state {int temperature; int wbdmux; int wbd_offset; scalar_t__ wbd_target; struct dib0090_wbd_slope* current_wbd_table; TYPE_2__* fe; } ;
typedef  int s32 ;
struct TYPE_3__ {int frequency; } ;
struct TYPE_4__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 scalar_t__ dib0090_wbd_to_db (struct dib0090_state*,int) ; 
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

u16 dib0090_get_wbd_target(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	u32 f_MHz = state->fe->dtv_property_cache.frequency / 1000000;
	s32 current_temp = state->temperature;
	s32 wbd_thot, wbd_tcold;
	const struct dib0090_wbd_slope *wbd = state->current_wbd_table;

	while (f_MHz > wbd->max_freq)
		wbd++;

	dprintk("using wbd-table-entry with max freq %d\n", wbd->max_freq);

	if (current_temp < 0)
		current_temp = 0;
	if (current_temp > 128)
		current_temp = 128;

	state->wbdmux &= ~(7 << 13);
	if (wbd->wbd_gain != 0)
		state->wbdmux |= (wbd->wbd_gain << 13);
	else
		state->wbdmux |= (4 << 13);

	dib0090_write_reg(state, 0x10, state->wbdmux);

	wbd_thot = wbd->offset_hot - (((u32) wbd->slope_hot * f_MHz) >> 6);
	wbd_tcold = wbd->offset_cold - (((u32) wbd->slope_cold * f_MHz) >> 6);

	wbd_tcold += ((wbd_thot - wbd_tcold) * current_temp) >> 7;

	state->wbd_target = dib0090_wbd_to_db(state, state->wbd_offset + wbd_tcold);
	dprintk("wbd-target: %d dB\n", (u32) state->wbd_target);
	dprintk("wbd offset applied is %d\n", wbd_tcold);

	return state->wbd_offset + wbd_tcold;
}