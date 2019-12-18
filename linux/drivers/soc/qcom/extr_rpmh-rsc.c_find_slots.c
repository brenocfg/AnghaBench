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
struct tcs_request {int num_cmds; TYPE_1__* cmds; } ;
struct tcs_group {int num_tcs; int ncpt; int offset; int /*<<< orphan*/ * cmd_cache; int /*<<< orphan*/  slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAX_TCS_SLOTS ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int find_match (struct tcs_group*,TYPE_1__*,int) ; 

__attribute__((used)) static int find_slots(struct tcs_group *tcs, const struct tcs_request *msg,
		      int *tcs_id, int *cmd_id)
{
	int slot, offset;
	int i = 0;

	/* Find if we already have the msg in our TCS */
	slot = find_match(tcs, msg->cmds, msg->num_cmds);
	if (slot >= 0)
		goto copy_data;

	/* Do over, until we can fit the full payload in a TCS */
	do {
		slot = bitmap_find_next_zero_area(tcs->slots, MAX_TCS_SLOTS,
						  i, msg->num_cmds, 0);
		if (slot >= tcs->num_tcs * tcs->ncpt)
			return -ENOMEM;
		i += tcs->ncpt;
	} while (slot + msg->num_cmds - 1 >= i);

copy_data:
	bitmap_set(tcs->slots, slot, msg->num_cmds);
	/* Copy the addresses of the resources over to the slots */
	for (i = 0; i < msg->num_cmds; i++)
		tcs->cmd_cache[slot + i] = msg->cmds[i].addr;

	offset = slot / tcs->ncpt;
	*tcs_id = offset + tcs->offset;
	*cmd_id = slot % tcs->ncpt;

	return 0;
}