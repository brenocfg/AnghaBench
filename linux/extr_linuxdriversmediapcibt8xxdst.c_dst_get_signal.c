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
struct dst_state {int diseq_flags; int decode_lock; int decode_strength; int decode_snr; scalar_t__ dst_type; int* rxbuffer; scalar_t__ cur_jiff; } ;

/* Variables and functions */
 int ATTEMPT_TUNE ; 
 scalar_t__ DST_TYPE_IS_ATSC ; 
 scalar_t__ DST_TYPE_IS_CABLE ; 
 scalar_t__ DST_TYPE_IS_SAT ; 
 scalar_t__ DST_TYPE_IS_TERR ; 
 int HAS_LOCK ; 
 int HZ ; 
 int dst_command (struct dst_state*,int*,int) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dst_get_signal(struct dst_state *state)
{
	int retval;
	u8 get_signal[] = { 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfb };
	//dprintk("%s: Getting Signal strength and other parameters\n", __func__);
	if ((state->diseq_flags & ATTEMPT_TUNE) == 0) {
		state->decode_lock = state->decode_strength = state->decode_snr = 0;
		return 0;
	}
	if (0 == (state->diseq_flags & HAS_LOCK)) {
		state->decode_lock = state->decode_strength = state->decode_snr = 0;
		return 0;
	}
	if (time_after_eq(jiffies, state->cur_jiff + (HZ / 5))) {
		retval = dst_command(state, get_signal, 8);
		if (retval < 0)
			return retval;
		if (state->dst_type == DST_TYPE_IS_SAT) {
			state->decode_lock = ((state->rxbuffer[6] & 0x10) == 0) ? 1 : 0;
			state->decode_strength = state->rxbuffer[5] << 8;
			state->decode_snr = state->rxbuffer[2] << 8 | state->rxbuffer[3];
		} else if ((state->dst_type == DST_TYPE_IS_TERR) || (state->dst_type == DST_TYPE_IS_CABLE)) {
			state->decode_lock = (state->rxbuffer[1]) ? 1 : 0;
			state->decode_strength = state->rxbuffer[4] << 8;
			state->decode_snr = state->rxbuffer[3] << 8;
		} else if (state->dst_type == DST_TYPE_IS_ATSC) {
			state->decode_lock = (state->rxbuffer[6] == 0x00) ? 1 : 0;
			state->decode_strength = state->rxbuffer[4] << 8;
			state->decode_snr = state->rxbuffer[2] << 8 | state->rxbuffer[3];
		}
		state->cur_jiff = jiffies;
	}
	return 0;
}