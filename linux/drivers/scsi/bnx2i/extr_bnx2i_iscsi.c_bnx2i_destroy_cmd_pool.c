#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_task {struct bnx2i_cmd* dd_data; } ;
struct iscsi_session {int cmds_max; struct iscsi_task** cmds; } ;
struct iscsi_bd {int dummy; } ;
struct bnx2i_hba {TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_tbl_dma; scalar_t__ bd_tbl; } ;
struct bnx2i_cmd {TYPE_2__ io_tbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ISCSI_MAX_BDS_PER_CMD ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_destroy_cmd_pool(struct bnx2i_hba *hba,
				   struct iscsi_session *session)
{
	int i;

	for (i = 0; i < session->cmds_max; i++) {
		struct iscsi_task *task = session->cmds[i];
		struct bnx2i_cmd *cmd = task->dd_data;

		if (cmd->io_tbl.bd_tbl)
			dma_free_coherent(&hba->pcidev->dev,
					  ISCSI_MAX_BDS_PER_CMD *
					  sizeof(struct iscsi_bd),
					  cmd->io_tbl.bd_tbl,
					  cmd->io_tbl.bd_tbl_dma);
	}

}