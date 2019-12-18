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
struct scsi_cmnd {int dummy; } ;
struct iscsi_tm {int opcode; int flags; int /*<<< orphan*/  rtt; } ;

/* Variables and functions */
 int ISCSI_FLAG_CMD_FINAL ; 
 int ISCSI_FLAG_TM_FUNC_MASK ; 
 int ISCSI_OP_IMMEDIATE ; 
 int ISCSI_OP_SCSI_TMFUNC ; 
 int ISCSI_TM_FUNC_TARGET_WARM_RESET ; 
 int /*<<< orphan*/  RESERVED_ITT ; 
 int /*<<< orphan*/  memset (struct iscsi_tm*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iscsi_prep_tgt_reset_pdu(struct scsi_cmnd *sc, struct iscsi_tm *hdr)
{
	memset(hdr, 0, sizeof(*hdr));
	hdr->opcode = ISCSI_OP_SCSI_TMFUNC | ISCSI_OP_IMMEDIATE;
	hdr->flags = ISCSI_TM_FUNC_TARGET_WARM_RESET & ISCSI_FLAG_TM_FUNC_MASK;
	hdr->flags |= ISCSI_FLAG_CMD_FINAL;
	hdr->rtt = RESERVED_ITT;
}