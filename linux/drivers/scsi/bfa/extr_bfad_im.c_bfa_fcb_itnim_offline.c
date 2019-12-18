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
struct TYPE_2__ {int flags; } ;
struct bfad_s {TYPE_1__ pport; } ;
struct bfad_port_s {int flags; int /*<<< orphan*/  im_port; struct bfad_s* bfad; } ;
struct bfad_itnim_s {int queue_work; int /*<<< orphan*/  itnim_work; int /*<<< orphan*/  state; int /*<<< orphan*/  im_port; int /*<<< orphan*/  fcs_itnim; struct bfad_im_s* im; } ;
struct bfad_im_s {int /*<<< orphan*/  drv_workq; } ;

/* Variables and functions */
 int BFAD_PORT_DELETE ; 
 int /*<<< orphan*/  ITNIM_STATE_OFFLINE ; 
 int /*<<< orphan*/  ITNIM_STATE_OFFLINE_PENDING ; 
 struct bfad_port_s* bfa_fcs_itnim_get_drvport (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
bfa_fcb_itnim_offline(struct bfad_itnim_s *itnim_drv)
{
	struct bfad_port_s    *port;
	struct bfad_s *bfad;
	struct bfad_im_s	*im = itnim_drv->im;

	port = bfa_fcs_itnim_get_drvport(&itnim_drv->fcs_itnim);
	bfad = port->bfad;
	if ((bfad->pport.flags & BFAD_PORT_DELETE) ||
		 (port->flags & BFAD_PORT_DELETE)) {
		itnim_drv->state = ITNIM_STATE_OFFLINE;
		return;
	}
	itnim_drv->im_port = port->im_port;
	itnim_drv->state = ITNIM_STATE_OFFLINE_PENDING;
	itnim_drv->queue_work = 1;

	/* ITNIM processing */
	if (itnim_drv->queue_work)
		queue_work(im->drv_workq, &itnim_drv->itnim_work);
}