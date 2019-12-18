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
struct dst_state {int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  rxbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  TUNER_TYPE_STV0299 ; 
 int /*<<< orphan*/  debug_dst_buffer (struct dst_state*) ; 
 int dst_check_sum (int*,int) ; 
 scalar_t__ dst_command (struct dst_state*,int*,int) ; 
 scalar_t__ memcmp (int**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int dst_check_stv0299(struct dst_state *state)
{
	u8 check_stv0299[] = { 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	check_stv0299[7] = dst_check_sum(check_stv0299, 7);
	if (dst_command(state, check_stv0299, 8) < 0) {
		pr_err("Cmd=[0x04] failed\n");
		return -1;
	}
	debug_dst_buffer(state);

	if (memcmp(&check_stv0299, &state->rxbuffer, 8)) {
		pr_err("Found a STV0299 NIM\n");
		state->tuner_type = TUNER_TYPE_STV0299;
		return 0;
	}

	return -1;
}