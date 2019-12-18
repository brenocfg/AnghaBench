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
struct dst_state {int type_flags; int* board_info; scalar_t__ dst_type; int /*<<< orphan*/  fw_name; int /*<<< orphan*/  dst_hw_cap; int /*<<< orphan*/  rxbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_TYPE_HAS_DBOARD ; 
 int DST_TYPE_HAS_MULTI_FE ; 
 int DST_TYPE_HAS_NEWTUNE_2 ; 
 int DST_TYPE_HAS_TS188 ; 
 int DST_TYPE_HAS_TS204 ; 
 scalar_t__ DST_TYPE_IS_ATSC ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int dst_check_sum (int*,int) ; 
 scalar_t__ dst_command (struct dst_state*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int dst_get_tuner_info(struct dst_state *state)
{
	u8 get_tuner_1[] = { 0x00, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	u8 get_tuner_2[] = { 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	get_tuner_1[7] = dst_check_sum(get_tuner_1, 7);
	get_tuner_2[7] = dst_check_sum(get_tuner_2, 7);
	pr_err("DST TYpe = MULTI FE\n");
	if (state->type_flags & DST_TYPE_HAS_MULTI_FE) {
		if (dst_command(state, get_tuner_1, 8) < 0) {
			dprintk(2, "Cmd=[0x13], Unsupported\n");
			goto force;
		}
	} else {
		if (dst_command(state, get_tuner_2, 8) < 0) {
			dprintk(2, "Cmd=[0xb], Unsupported\n");
			goto force;
		}
	}
	memcpy(&state->board_info, &state->rxbuffer, 8);
	if (state->type_flags & DST_TYPE_HAS_MULTI_FE) {
		pr_err("DST type has TS=188\n");
	}
	if (state->board_info[0] == 0xbc) {
		if (state->dst_type != DST_TYPE_IS_ATSC)
			state->type_flags |= DST_TYPE_HAS_TS188;
		else
			state->type_flags |= DST_TYPE_HAS_NEWTUNE_2;

		if (state->board_info[1] == 0x01) {
			state->dst_hw_cap |= DST_TYPE_HAS_DBOARD;
			pr_err("DST has Daughterboard\n");
		}
	}

	return 0;
force:
	if (!strncmp(state->fw_name, "DCT-CI", 6)) {
		state->type_flags |= DST_TYPE_HAS_TS204;
		pr_err("Forcing [%s] to TS188\n", state->fw_name);
	}

	return -1;
}