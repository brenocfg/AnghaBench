#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nents; } ;
struct TYPE_4__ {TYPE_3__ table; } ;
struct scsi_cmnd {TYPE_2__* prot_sdb; TYPE_1__ sdb; } ;
struct TYPE_5__ {TYPE_3__ table; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_INLINE_PROT_SG_CNT ; 
 int /*<<< orphan*/  SCSI_INLINE_SG_CNT ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_free_table_chained (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_mq_free_sgtables(struct scsi_cmnd *cmd)
{
	if (cmd->sdb.table.nents)
		sg_free_table_chained(&cmd->sdb.table,
				SCSI_INLINE_SG_CNT);
	if (scsi_prot_sg_count(cmd))
		sg_free_table_chained(&cmd->prot_sdb->table,
				SCSI_INLINE_PROT_SG_CNT);
}