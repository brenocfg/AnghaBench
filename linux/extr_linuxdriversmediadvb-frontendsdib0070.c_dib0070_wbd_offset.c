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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int frequency; } ;
struct dvb_frontend {TYPE_2__ dtv_property_cache; struct dib0070_state* tuner_priv; } ;
struct dib0070_wbd_gain_cfg {int freq; int wbd_gain_val; } ;
struct dib0070_state {int wbd_gain_current; int /*<<< orphan*/ * wbd_offset_3_3; TYPE_1__* cfg; } ;
struct TYPE_3__ {struct dib0070_wbd_gain_cfg* wbd_gain; } ;

/* Variables and functions */

u16 dib0070_wbd_offset(struct dvb_frontend *fe)
{
	struct dib0070_state *state = fe->tuner_priv;
	const struct dib0070_wbd_gain_cfg *tmp = state->cfg->wbd_gain;
	u32 freq = fe->dtv_property_cache.frequency/1000;

	if (tmp != NULL) {
		while (freq/1000 > tmp->freq) /* find the right one */
			tmp++;
		state->wbd_gain_current = tmp->wbd_gain_val;
	} else
		state->wbd_gain_current = 6;

	return state->wbd_offset_3_3[state->wbd_gain_current - 6];
}