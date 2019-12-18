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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfad_itnim_s {int /*<<< orphan*/  scsi_tgt_id; TYPE_2__* im_port; } ;
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_itnim_s {struct bfad_itnim_s* itnim_drv; } ;
struct bfa_bsg_rport_scsi_addr_s {void* status; scalar_t__ lun; scalar_t__ bus; int /*<<< orphan*/  target; int /*<<< orphan*/  host; int /*<<< orphan*/  rpwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  vf_id; } ;
struct TYPE_4__ {TYPE_1__* shost; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 void* BFA_STATUS_OK ; 
 void* BFA_STATUS_UNKNOWN_LWWN ; 
 void* BFA_STATUS_UNKNOWN_RWWN ; 
 struct bfa_fcs_itnim_s* bfa_fcs_itnim_lookup (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 struct bfa_fcs_lport_s* bfa_fcs_lookup_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
bfad_iocmd_rport_get_addr(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_rport_scsi_addr_s *iocmd =
			(struct bfa_bsg_rport_scsi_addr_s *)cmd;
	struct bfa_fcs_lport_s	*fcs_port;
	struct bfa_fcs_itnim_s	*fcs_itnim;
	struct bfad_itnim_s	*drv_itnim;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	if (fcs_port == NULL) {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		goto out;
	}

	fcs_itnim = bfa_fcs_itnim_lookup(fcs_port, iocmd->rpwwn);
	if (fcs_itnim == NULL) {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		goto out;
	}

	drv_itnim = fcs_itnim->itnim_drv;

	if (drv_itnim && drv_itnim->im_port)
		iocmd->host = drv_itnim->im_port->shost->host_no;
	else {
		bfa_trc(bfad, 0);
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		goto out;
	}

	iocmd->target = drv_itnim->scsi_tgt_id;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->bus = 0;
	iocmd->lun = 0;
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}