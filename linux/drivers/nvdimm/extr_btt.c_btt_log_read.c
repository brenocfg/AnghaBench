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
struct log_group {TYPE_1__* ent; } ;
struct log_entry {int dummy; } ;
struct arena_info {size_t* log_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LOG_ENT_SIZE ; 
 int btt_log_get_old (struct arena_info*,struct log_group*) ; 
 int btt_log_group_read (struct arena_info*,int /*<<< orphan*/ ,struct log_group*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct log_entry*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dev (struct arena_info*) ; 

__attribute__((used)) static int btt_log_read(struct arena_info *arena, u32 lane,
			struct log_entry *ent, int old_flag)
{
	int ret;
	int old_ent, ret_ent;
	struct log_group log;

	ret = btt_log_group_read(arena, lane, &log);
	if (ret)
		return -EIO;

	old_ent = btt_log_get_old(arena, &log);
	if (old_ent < 0 || old_ent > 1) {
		dev_err(to_dev(arena),
				"log corruption (%d): lane %d seq [%d, %d]\n",
				old_ent, lane, log.ent[arena->log_index[0]].seq,
				log.ent[arena->log_index[1]].seq);
		/* TODO set error state? */
		return -EIO;
	}

	ret_ent = (old_flag ? old_ent : (1 - old_ent));

	if (ent != NULL)
		memcpy(ent, &log.ent[arena->log_index[ret_ent]], LOG_ENT_SIZE);

	return ret_ent;
}