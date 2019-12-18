#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ufshcd_lrb {TYPE_6__* ucd_req_ptr; TYPE_4__* cmd; } ;
struct ufs_hba {int /*<<< orphan*/  dev; struct ufshcd_lrb* lrb; } ;
typedef  int sector_t ;
struct TYPE_11__ {int /*<<< orphan*/  exp_data_transfer_len; } ;
struct TYPE_12__ {TYPE_5__ sc; } ;
struct TYPE_10__ {TYPE_3__* request; scalar_t__* cmnd; } ;
struct TYPE_9__ {TYPE_2__* bio; } ;
struct TYPE_7__ {int bi_sector; } ;
struct TYPE_8__ {TYPE_1__ bi_iter; } ;

/* Variables and functions */
 scalar_t__ READ_10 ; 
 int /*<<< orphan*/  REG_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  REG_UTP_TRANSFER_REQ_DOOR_BELL ; 
 scalar_t__ WRITE_10 ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_command (int /*<<< orphan*/ ,char const*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  trace_ufshcd_command_enabled () ; 
 int /*<<< orphan*/  ufshcd_add_cmd_upiu_trace (struct ufs_hba*,unsigned int,char const*) ; 
 int /*<<< orphan*/  ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufshcd_add_command_trace(struct ufs_hba *hba,
		unsigned int tag, const char *str)
{
	sector_t lba = -1;
	u8 opcode = 0;
	u32 intr, doorbell;
	struct ufshcd_lrb *lrbp = &hba->lrb[tag];
	int transfer_len = -1;

	if (!trace_ufshcd_command_enabled()) {
		/* trace UPIU W/O tracing command */
		if (lrbp->cmd)
			ufshcd_add_cmd_upiu_trace(hba, tag, str);
		return;
	}

	if (lrbp->cmd) { /* data phase exists */
		/* trace UPIU also */
		ufshcd_add_cmd_upiu_trace(hba, tag, str);
		opcode = (u8)(*lrbp->cmd->cmnd);
		if ((opcode == READ_10) || (opcode == WRITE_10)) {
			/*
			 * Currently we only fully trace read(10) and write(10)
			 * commands
			 */
			if (lrbp->cmd->request && lrbp->cmd->request->bio)
				lba =
				  lrbp->cmd->request->bio->bi_iter.bi_sector;
			transfer_len = be32_to_cpu(
				lrbp->ucd_req_ptr->sc.exp_data_transfer_len);
		}
	}

	intr = ufshcd_readl(hba, REG_INTERRUPT_STATUS);
	doorbell = ufshcd_readl(hba, REG_UTP_TRANSFER_REQ_DOOR_BELL);
	trace_ufshcd_command(dev_name(hba->dev), str, tag,
				doorbell, transfer_len, intr, lba, opcode);
}