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
struct bfad_itnim_s {int dummy; } ;
struct bfa_fcs_rport_s {int /*<<< orphan*/  fcs; int /*<<< orphan*/  pwwn; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_lport_s {TYPE_1__* fcs; } ;
struct bfa_fcs_itnim_s {void* task_retry_id; void* conf_comp; void* rec_support; void* seq_rec; int /*<<< orphan*/ * bfa_itnim; struct bfad_itnim_s* itnim_drv; int /*<<< orphan*/  fcs; struct bfa_fcs_rport_s* rport; } ;
struct TYPE_2__ {int /*<<< orphan*/  bfad; } ;

/* Variables and functions */
 void* BFA_FALSE ; 
 int bfa_fcb_itnim_alloc (int /*<<< orphan*/ ,struct bfa_fcs_itnim_s**,struct bfad_itnim_s**) ; 
 int /*<<< orphan*/  bfa_fcs_itnim_sm_offline ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int /*<<< orphan*/ ) ; 

struct bfa_fcs_itnim_s *
bfa_fcs_itnim_create(struct bfa_fcs_rport_s *rport)
{
	struct bfa_fcs_lport_s *port = rport->port;
	struct bfa_fcs_itnim_s *itnim;
	struct bfad_itnim_s   *itnim_drv;
	int ret;

	/*
	 * call bfad to allocate the itnim
	 */
	ret = bfa_fcb_itnim_alloc(port->fcs->bfad, &itnim, &itnim_drv);
	if (ret) {
		bfa_trc(port->fcs, rport->pwwn);
		return NULL;
	}

	/*
	 * Initialize itnim
	 */
	itnim->rport = rport;
	itnim->fcs = rport->fcs;
	itnim->itnim_drv = itnim_drv;

	itnim->bfa_itnim     = NULL;
	itnim->seq_rec	     = BFA_FALSE;
	itnim->rec_support   = BFA_FALSE;
	itnim->conf_comp     = BFA_FALSE;
	itnim->task_retry_id = BFA_FALSE;

	/*
	 * Set State machine
	 */
	bfa_sm_set_state(itnim, bfa_fcs_itnim_sm_offline);

	return itnim;
}