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
struct bfad_port_s {int /*<<< orphan*/  im_port; } ;
struct bfad_itnim_s {int queue_work; int /*<<< orphan*/  itnim_work; int /*<<< orphan*/  im_port; int /*<<< orphan*/  state; int /*<<< orphan*/  fcs_itnim; int /*<<< orphan*/  bfa_itnim; struct bfad_im_s* im; } ;
struct bfad_im_s {int /*<<< orphan*/  drv_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITNIM_STATE_ONLINE ; 
 struct bfad_port_s* bfa_fcs_itnim_get_drvport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_get_halitn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bfa_fcb_itnim_online(struct bfad_itnim_s *itnim_drv)
{
	struct bfad_port_s    *port;
	struct bfad_im_s	*im = itnim_drv->im;

	itnim_drv->bfa_itnim = bfa_fcs_itnim_get_halitn(&itnim_drv->fcs_itnim);
	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	itnim_drv->state = ITNIM_STATE_ONLINE;
	itnim_drv->queue_work = 1;
	itnim_drv->im_port = port->im_port;

	/* ITNIM processing */
	if (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
}