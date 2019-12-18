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
struct vnic_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  active_fw_reqs; } ;
struct TYPE_7__ {TYPE_2__ fw_stats; } ;
struct fnic {TYPE_1__* lport; TYPE_3__ fnic_stats; } ;
struct TYPE_8__ {int type; } ;
struct fcpio_fw_req {TYPE_4__ hdr; } ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
#define  FCPIO_ACK 133 
#define  FCPIO_FLOGI_FIP_REG_CMPL 132 
#define  FCPIO_FLOGI_REG_CMPL 131 
#define  FCPIO_ICMND_CMPL 130 
#define  FCPIO_ITMF_CMPL 129 
#define  FCPIO_RESET_CMPL 128 
 int /*<<< orphan*/  FNIC_SCSI_DBG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  atomic64_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnic_fcpio_ack_handler (struct fnic*,unsigned int,struct fcpio_fw_req*) ; 
 int /*<<< orphan*/  fnic_fcpio_flogi_reg_cmpl_handler (struct fnic*,struct fcpio_fw_req*) ; 
 int /*<<< orphan*/  fnic_fcpio_fw_reset_cmpl_handler (struct fnic*,struct fcpio_fw_req*) ; 
 int /*<<< orphan*/  fnic_fcpio_icmnd_cmpl_handler (struct fnic*,struct fcpio_fw_req*) ; 
 int /*<<< orphan*/  fnic_fcpio_itmf_cmpl_handler (struct fnic*,struct fcpio_fw_req*) ; 
 struct fnic* vnic_dev_priv (struct vnic_dev*) ; 

__attribute__((used)) static int fnic_fcpio_cmpl_handler(struct vnic_dev *vdev,
				   unsigned int cq_index,
				   struct fcpio_fw_req *desc)
{
	struct fnic *fnic = vnic_dev_priv(vdev);

	switch (desc->hdr.type) {
	case FCPIO_ICMND_CMPL: /* fw completed a command */
	case FCPIO_ITMF_CMPL: /* fw completed itmf (abort cmd, lun reset)*/
	case FCPIO_FLOGI_REG_CMPL: /* fw completed flogi_reg */
	case FCPIO_FLOGI_FIP_REG_CMPL: /* fw completed flogi_fip_reg */
	case FCPIO_RESET_CMPL: /* fw completed reset */
		atomic64_dec(&fnic->fnic_stats.fw_stats.active_fw_reqs);
		break;
	default:
		break;
	}

	switch (desc->hdr.type) {
	case FCPIO_ACK: /* fw copied copy wq desc to its queue */
		fnic_fcpio_ack_handler(fnic, cq_index, desc);
		break;

	case FCPIO_ICMND_CMPL: /* fw completed a command */
		fnic_fcpio_icmnd_cmpl_handler(fnic, desc);
		break;

	case FCPIO_ITMF_CMPL: /* fw completed itmf (abort cmd, lun reset)*/
		fnic_fcpio_itmf_cmpl_handler(fnic, desc);
		break;

	case FCPIO_FLOGI_REG_CMPL: /* fw completed flogi_reg */
	case FCPIO_FLOGI_FIP_REG_CMPL: /* fw completed flogi_fip_reg */
		fnic_fcpio_flogi_reg_cmpl_handler(fnic, desc);
		break;

	case FCPIO_RESET_CMPL: /* fw completed reset */
		fnic_fcpio_fw_reset_cmpl_handler(fnic, desc);
		break;

	default:
		FNIC_SCSI_DBG(KERN_DEBUG, fnic->lport->host,
			      "firmware completion type %d\n",
			      desc->hdr.type);
		break;
	}

	return 0;
}