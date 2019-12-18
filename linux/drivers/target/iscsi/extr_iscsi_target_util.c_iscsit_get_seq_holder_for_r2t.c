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
typedef  size_t u32 ;
struct iscsi_seq {scalar_t__ type; scalar_t__ seq_send_order; } ;
struct iscsi_cmd {size_t seq_count; scalar_t__ seq_send_order; struct iscsi_seq* seq_list; } ;

/* Variables and functions */
 scalar_t__ SEQTYPE_NORMAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

struct iscsi_seq *iscsit_get_seq_holder_for_r2t(struct iscsi_cmd *cmd)
{
	u32 i;

	if (!cmd->seq_list) {
		pr_err("struct iscsi_cmd->seq_list is NULL!\n");
		return NULL;
	}

	for (i = 0; i < cmd->seq_count; i++) {
		if (cmd->seq_list[i].type != SEQTYPE_NORMAL)
			continue;
		if (cmd->seq_list[i].seq_send_order == cmd->seq_send_order) {
			cmd->seq_send_order++;
			return &cmd->seq_list[i];
		}
	}

	return NULL;
}