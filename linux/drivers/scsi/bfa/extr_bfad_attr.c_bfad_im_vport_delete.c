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
typedef  int /*<<< orphan*/  wwn_t ;
typedef  int /*<<< orphan*/  u8 ;
struct fc_vport {scalar_t__ dd_data; } ;
struct completion {int dummy; } ;
struct TYPE_4__ {int flags; TYPE_1__* im_port; } ;
struct bfad_vport_s {int /*<<< orphan*/  list_entry; struct completion* comp_del; TYPE_2__ drv_port; int /*<<< orphan*/  fcs_vport; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfad_im_port_s {int flags; struct bfad_s* bfad; } ;
struct bfa_fcs_vport_s {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_3__ {struct Scsi_Host* shost; } ;

/* Variables and functions */
 int BFAD_PORT_DELETE ; 
 int BFA_STATUS_PBC ; 
 int VPCERR_BAD_WWN ; 
 int bfa_fcs_vport_delete (int /*<<< orphan*/ *) ; 
 struct bfa_fcs_vport_s* bfa_fcs_vport_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_scsi_host_free (struct bfad_s*,struct bfad_im_port_s*) ; 
 int /*<<< orphan*/  fc_host_port_name (struct Scsi_Host*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 int /*<<< orphan*/  kfree (struct bfad_vport_s*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  u64_to_wwn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (struct completion*) ; 

__attribute__((used)) static int
bfad_im_vport_delete(struct fc_vport *fc_vport)
{
	struct bfad_vport_s *vport = (struct bfad_vport_s *)fc_vport->dd_data;
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) vport->drv_port.im_port;
	struct bfad_s *bfad = im_port->bfad;
	struct bfa_fcs_vport_s *fcs_vport;
	struct Scsi_Host *vshost;
	wwn_t   pwwn;
	int rc;
	unsigned long flags;
	struct completion fcomp;

	if (im_port->flags & BFAD_PORT_DELETE) {
		bfad_scsi_host_free(bfad, im_port);
		list_del(&vport->list_entry);
		kfree(vport);
		return 0;
	}

	vshost = vport->drv_port.im_port->shost;
	u64_to_wwn(fc_host_port_name(vshost), (u8 *)&pwwn);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs, 0, pwwn);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (fcs_vport == NULL)
		return VPCERR_BAD_WWN;

	vport->drv_port.flags |= BFAD_PORT_DELETE;

	vport->comp_del = &fcomp;
	init_completion(vport->comp_del);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	rc = bfa_fcs_vport_delete(&vport->fcs_vport);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (rc == BFA_STATUS_PBC) {
		vport->drv_port.flags &= ~BFAD_PORT_DELETE;
		vport->comp_del = NULL;
		return -1;
	}

	wait_for_completion(vport->comp_del);

	bfad_scsi_host_free(bfad, im_port);
	list_del(&vport->list_entry);
	kfree(vport);

	return 0;
}