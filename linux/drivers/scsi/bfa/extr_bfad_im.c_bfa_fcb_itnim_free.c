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
typedef  int /*<<< orphan*/  u32 ;
struct bfad_s {int dummy; } ;
struct bfad_port_s {TYPE_2__* im_port; } ;
struct bfad_itnim_s {scalar_t__ state; int queue_work; int /*<<< orphan*/  itnim_work; int /*<<< orphan*/  fcs_itnim; TYPE_2__* im_port; struct bfad_im_s* im; } ;
struct bfad_im_s {int /*<<< orphan*/  drv_workq; } ;
struct TYPE_4__ {TYPE_1__* shost; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ITNIM_STATE_FREE ; 
 scalar_t__ ITNIM_STATE_OFFLINE_PENDING ; 
 scalar_t__ ITNIM_STATE_ONLINE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct bfad_port_s* bfa_fcs_itnim_get_drvport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_fcid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_pwwn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  fcid2str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wwn2str (char*,int /*<<< orphan*/ ) ; 

void
bfa_fcb_itnim_free(struct bfad_s *bfad, struct bfad_itnim_s *itnim_drv)
{
	struct bfad_port_s    *port;
	wwn_t wwpn;
	u32 fcid;
	char wwpn_str[32], fcid_str[16];
	struct bfad_im_s	*im = itnim_drv->im;

	/* online to free state transtion should not happen */
	WARN_ON(itnim_drv->state == ITNIM_STATE_ONLINE);

	itnim_drv->queue_work = 1;
	/* offline request is not yet done, use the same request to free */
	if (itnim_drv->state == ITNIM_STATE_OFFLINE_PENDING)
		itnim_drv->queue_work = 0;

	itnim_drv->state = ITNIM_STATE_FREE;
	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	itnim_drv->im_port = port->im_port;
	wwpn = bfa_fcs_itnim_get_pwwn(&itnim_drv->fcs_itnim);
	fcid = bfa_fcs_itnim_get_fcid(&itnim_drv->fcs_itnim);
	wwn2str(wwpn_str, wwpn);
	fcid2str(fcid_str, fcid);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level,
		"ITNIM FREE scsi%d: FCID: %s WWPN: %s\n",
		port->im_port->shost->host_no,
		fcid_str, wwpn_str);

	/* ITNIM processing */
	if (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
}