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
typedef  void* u8 ;
typedef  int u32 ;
struct dst_state {int frequency; scalar_t__ dst_type; int* tx_tuna; int type_flags; int dst_hw_cap; } ;

/* Variables and functions */
 int DST_TYPE_HAS_ANALOG ; 
 int DST_TYPE_HAS_OBS_REGS ; 
 scalar_t__ DST_TYPE_IS_ATSC ; 
 scalar_t__ DST_TYPE_IS_CABLE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 

__attribute__((used)) static int dst_set_freq(struct dst_state *state, u32 freq)
{
	state->frequency = freq;
	dprintk(2, "set Frequency %u\n", freq);

	if (state->dst_type == DST_TYPE_IS_SAT) {
		freq = freq / 1000;
		if (freq < 950 || freq > 2150)
			return -EINVAL;
		state->tx_tuna[2] = (freq >> 8);
		state->tx_tuna[3] = (u8) freq;
		state->tx_tuna[4] = 0x01;
		state->tx_tuna[8] &= ~0x04;
		if (state->type_flags & DST_TYPE_HAS_OBS_REGS) {
			if (freq < 1531)
				state->tx_tuna[8] |= 0x04;
		}
	} else if (state->dst_type == DST_TYPE_IS_TERR) {
		freq = freq / 1000;
		if (freq < 137000 || freq > 858000)
			return -EINVAL;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
	} else if (state->dst_type == DST_TYPE_IS_CABLE) {
		freq = freq / 1000;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >> 8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
	} else if (state->dst_type == DST_TYPE_IS_ATSC) {
		freq = freq / 1000;
		if (freq < 51000 || freq > 858000)
			return -EINVAL;
		state->tx_tuna[2] = (freq >> 16) & 0xff;
		state->tx_tuna[3] = (freq >>  8) & 0xff;
		state->tx_tuna[4] = (u8) freq;
		state->tx_tuna[5] = 0x00;		/*	ATSC	*/
		state->tx_tuna[6] = 0x00;
		if (state->dst_hw_cap & DST_TYPE_HAS_ANALOG)
			state->tx_tuna[7] = 0x00;	/*	Digital	*/
	} else
		return -EINVAL;

	return 0;
}