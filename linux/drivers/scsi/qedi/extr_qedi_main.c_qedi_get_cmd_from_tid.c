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
typedef  size_t u32 ;
struct qedi_ctx {TYPE_1__* itt_map; } ;
struct qedi_cmd {size_t task_id; } ;
struct TYPE_2__ {struct qedi_cmd* p_cmd; } ;

/* Variables and functions */
 size_t MAX_ISCSI_TASK_ENTRIES ; 

struct qedi_cmd *qedi_get_cmd_from_tid(struct qedi_ctx *qedi, u32 tid)
{
	struct qedi_cmd *cmd = NULL;

	if (tid >= MAX_ISCSI_TASK_ENTRIES)
		return NULL;

	cmd = qedi->itt_map[tid].p_cmd;
	if (cmd->task_id != tid)
		return NULL;

	qedi->itt_map[tid].p_cmd = NULL;

	return cmd;
}