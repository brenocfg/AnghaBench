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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct dib0090_state {scalar_t__ current_band; scalar_t__ wbd_target; scalar_t__ wbd_offset; TYPE_1__* config; } ;
struct TYPE_2__ {int wbd_vhf_offset; int wbd_cband_offset; } ;

/* Variables and functions */
 scalar_t__ BAND_CBAND ; 
 scalar_t__ BAND_VHF ; 
 scalar_t__ dib0090_wbd_to_db (struct dib0090_state*,scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib0090_wbd_target(struct dib0090_state *state, u32 rf)
{
	u16 offset = 250;

	/* TODO : DAB digital N+/-1 interferer perfs : offset = 10 */

	if (state->current_band == BAND_VHF)
		offset = 650;
#ifndef FIRMWARE_FIREFLY
	if (state->current_band == BAND_VHF)
		offset = state->config->wbd_vhf_offset;
	if (state->current_band == BAND_CBAND)
		offset = state->config->wbd_cband_offset;
#endif

	state->wbd_target = dib0090_wbd_to_db(state, state->wbd_offset + offset);
	dprintk("wbd-target: %d dB\n", (u32) state->wbd_target);
}