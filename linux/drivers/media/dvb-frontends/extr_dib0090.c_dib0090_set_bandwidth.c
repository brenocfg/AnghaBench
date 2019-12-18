#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {scalar_t__ in_soc; } ;
struct dib0090_state {int bb_1_def; TYPE_3__ identity; TYPE_2__* fe; } ;
struct TYPE_4__ {int bandwidth_hz; } ;
struct TYPE_5__ {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int,int) ; 

__attribute__((used)) static void dib0090_set_bandwidth(struct dib0090_state *state)
{
	u16 tmp;

	if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 5000)
		tmp = (3 << 14);
	else if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 6000)
		tmp = (2 << 14);
	else if (state->fe->dtv_property_cache.bandwidth_hz / 1000 <= 7000)
		tmp = (1 << 14);
	else
		tmp = (0 << 14);

	state->bb_1_def &= 0x3fff;
	state->bb_1_def |= tmp;

	dib0090_write_reg(state, 0x01, state->bb_1_def);	/* be sure that we have the right bb-filter */

	dib0090_write_reg(state, 0x03, 0x6008);	/* = 0x6008 : vcm3_trim = 1 ; filter2_gm1_trim = 8 ; filter2_cutoff_freq = 0 */
	dib0090_write_reg(state, 0x04, 0x1);	/* 0 = 1KHz ; 1 = 50Hz ; 2 = 150Hz ; 3 = 50KHz ; 4 = servo fast */
	if (state->identity.in_soc) {
		dib0090_write_reg(state, 0x05, 0x9bcf); /* attenuator_ibias_tri = 2 ; input_stage_ibias_tr = 1 ; nc = 11 ; ext_gm_trim = 1 ; obuf_ibias_trim = 4 ; filter13_gm2_ibias_t = 15 */
	} else {
		dib0090_write_reg(state, 0x02, (5 << 11) | (8 << 6) | (22 & 0x3f));	/* 22 = cap_value */
		dib0090_write_reg(state, 0x05, 0xabcd);	/* = 0xabcd : attenuator_ibias_tri = 2 ; input_stage_ibias_tr = 2 ; nc = 11 ; ext_gm_trim = 1 ; obuf_ibias_trim = 4 ; filter13_gm2_ibias_t = 13 */
	}
}