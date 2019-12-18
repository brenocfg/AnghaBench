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
struct iscsi_task {int hdr_max; int /*<<< orphan*/ * hdr; struct bnx2i_cmd* dd_data; } ;
struct iscsi_session {int cmds_max; struct iscsi_task** cmds; } ;
struct iscsi_hdr {int dummy; } ;
struct bnx2i_hba {int dummy; } ;
struct bnx2i_cmd {int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ bnx2i_alloc_bdt (struct bnx2i_hba*,struct iscsi_session*,struct bnx2i_cmd*) ; 
 int /*<<< orphan*/  bnx2i_destroy_cmd_pool (struct bnx2i_hba*,struct iscsi_session*) ; 

__attribute__((used)) static int bnx2i_setup_cmd_pool(struct bnx2i_hba *hba,
				struct iscsi_session *session)
{
	int i;

	for (i = 0; i < session->cmds_max; i++) {
		struct iscsi_task *task = session->cmds[i];
		struct bnx2i_cmd *cmd = task->dd_data;

		task->hdr = &cmd->hdr;
		task->hdr_max = sizeof(struct iscsi_hdr);

		if (bnx2i_alloc_bdt(hba, session, cmd))
			goto free_bdts;
	}

	return 0;

free_bdts:
	bnx2i_destroy_cmd_pool(hba, session);
	return -ENOMEM;
}