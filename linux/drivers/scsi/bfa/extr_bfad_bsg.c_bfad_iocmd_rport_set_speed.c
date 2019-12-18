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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct TYPE_2__ {scalar_t__ rpsc_speed; int /*<<< orphan*/  assigned_speed; } ;
struct bfa_fcs_rport_s {scalar_t__ bfa_rport; TYPE_1__ rpf; } ;
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_bsg_rport_set_speed_s {int /*<<< orphan*/  status; int /*<<< orphan*/  speed; int /*<<< orphan*/  rpwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 scalar_t__ BFA_PORT_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_LWWN ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_RWWN ; 
 struct bfa_fcs_lport_s* bfa_fcs_lookup_port (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bfa_fcs_rport_s* bfa_fcs_rport_lookup (struct bfa_fcs_lport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_rport_speed (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_rport_set_speed(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_rport_set_speed_s *iocmd =
				(struct bfa_bsg_rport_set_speed_s *)cmd;
	struct bfa_fcs_lport_s *fcs_port;
	struct bfa_fcs_rport_s *fcs_rport;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_port = bfa_fcs_lookup_port(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->pwwn);
	if (fcs_port == NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_LWWN;
		goto out;
	}

	fcs_rport = bfa_fcs_rport_lookup(fcs_port, iocmd->rpwwn);
	if (fcs_rport == NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_RWWN;
		goto out;
	}

	fcs_rport->rpf.assigned_speed  = iocmd->speed;
	/* Set this speed in f/w only if the RPSC speed is not available */
	if (fcs_rport->rpf.rpsc_speed == BFA_PORT_SPEED_UNKNOWN)
		if (fcs_rport->bfa_rport)
			bfa_rport_speed(fcs_rport->bfa_rport, iocmd->speed);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}