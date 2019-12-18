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
struct dst_state {scalar_t__ dst_type; int* tx_tuna; } ;

/* Variables and functions */
 scalar_t__ DST_TYPE_IS_SAT ; 
 int EOPNOTSUPP ; 
 int dst_check_sum (int*,int) ; 
 int dst_command (struct dst_state*,int*,int) ; 

__attribute__((used)) static int dst_tone_power_cmd(struct dst_state *state)
{
	u8 packet[8] = { 0x00, 0x09, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00 };

	if (state->dst_type != DST_TYPE_IS_SAT)
		return -EOPNOTSUPP;
	packet[4] = state->tx_tuna[4];
	packet[2] = state->tx_tuna[2];
	packet[3] = state->tx_tuna[3];
	packet[7] = dst_check_sum (packet, 7);
	return dst_command(state, packet, 8);
}