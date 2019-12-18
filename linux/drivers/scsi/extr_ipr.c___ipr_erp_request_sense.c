#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ioasc; } ;
struct TYPE_7__ {TYPE_2__ hdr; } ;
struct TYPE_8__ {TYPE_3__ ioasa; } ;
struct ipr_cmd_pkt {int /*<<< orphan*/  timeout; int /*<<< orphan*/  flags_hi; int /*<<< orphan*/ * cdb; int /*<<< orphan*/  request_type; } ;
struct TYPE_5__ {struct ipr_cmd_pkt cmd_pkt; } ;
struct ipr_cmnd {int /*<<< orphan*/  sense_buffer_dma; TYPE_4__ s; TYPE_1__ ioarcb; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPR_FLAGS_HI_NO_ULEN_CHK ; 
 int /*<<< orphan*/  IPR_FLAGS_HI_SYNC_OVERRIDE ; 
 int /*<<< orphan*/  IPR_IOADL_FLAGS_READ_LAST ; 
 scalar_t__ IPR_IOASC_SENSE_KEY (int /*<<< orphan*/ ) ; 
 int IPR_REQUEST_SENSE_TIMEOUT ; 
 int /*<<< orphan*/  IPR_RQTYPE_SCSICDB ; 
 int /*<<< orphan*/  REQUEST_SENSE ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  __ipr_erp_done (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  ipr_do_req (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipr_erp_done ; 
 int /*<<< orphan*/  ipr_init_ioadl (struct ipr_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_reinit_ipr_cmnd_for_erp (struct ipr_cmnd*) ; 
 int /*<<< orphan*/  ipr_timeout ; 

__attribute__((used)) static void __ipr_erp_request_sense(struct ipr_cmnd *ipr_cmd)
{
	struct ipr_cmd_pkt *cmd_pkt = &ipr_cmd->ioarcb.cmd_pkt;
	u32 ioasc = be32_to_cpu(ipr_cmd->s.ioasa.hdr.ioasc);

	if (IPR_IOASC_SENSE_KEY(ioasc) > 0) {
		__ipr_erp_done(ipr_cmd);
		return;
	}

	ipr_reinit_ipr_cmnd_for_erp(ipr_cmd);

	cmd_pkt->request_type = IPR_RQTYPE_SCSICDB;
	cmd_pkt->cdb[0] = REQUEST_SENSE;
	cmd_pkt->cdb[4] = SCSI_SENSE_BUFFERSIZE;
	cmd_pkt->flags_hi |= IPR_FLAGS_HI_SYNC_OVERRIDE;
	cmd_pkt->flags_hi |= IPR_FLAGS_HI_NO_ULEN_CHK;
	cmd_pkt->timeout = cpu_to_be16(IPR_REQUEST_SENSE_TIMEOUT / HZ);

	ipr_init_ioadl(ipr_cmd, ipr_cmd->sense_buffer_dma,
		       SCSI_SENSE_BUFFERSIZE, IPR_IOADL_FLAGS_READ_LAST);

	ipr_do_req(ipr_cmd, ipr_erp_done, ipr_timeout,
		   IPR_REQUEST_SENSE_TIMEOUT * 2);
}