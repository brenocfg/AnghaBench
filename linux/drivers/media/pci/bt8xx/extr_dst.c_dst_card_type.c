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
struct tuner_types {int /*<<< orphan*/  tuner_type; int /*<<< orphan*/  tuner_name; int /*<<< orphan*/  board_name; } ;
struct dst_state {int /*<<< orphan*/  tuner_type; int /*<<< orphan*/ * card_info; int /*<<< orphan*/  rxbuffer; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tuner_types*) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int dst_check_sum (int*,int) ; 
 scalar_t__ dst_command (struct dst_state*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,char,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tuner_types* tuner_list ; 

__attribute__((used)) static int dst_card_type(struct dst_state *state)
{
	int j;
	struct tuner_types *p_tuner_list = NULL;

	u8 get_type[] = { 0x00, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	get_type[7] = dst_check_sum(get_type, 7);
	if (dst_command(state, get_type, 8) < 0) {
		dprintk(2, "Unsupported Command\n");
		return -1;
	}
	memset(&state->card_info, '\0', 8);
	memcpy(&state->card_info, &state->rxbuffer, 7);
	pr_err("Device Model=[%s]\n", &state->card_info[0]);

	for (j = 0, p_tuner_list = tuner_list; j < ARRAY_SIZE(tuner_list); j++, p_tuner_list++) {
		if (!strcmp(&state->card_info[0], p_tuner_list->board_name)) {
			state->tuner_type = p_tuner_list->tuner_type;
			pr_err("DST has [%s] tuner, tuner type=[%d]\n",
				p_tuner_list->tuner_name, p_tuner_list->tuner_type);
		}
	}

	return 0;
}