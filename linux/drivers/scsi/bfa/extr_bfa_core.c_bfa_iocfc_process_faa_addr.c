#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pbc_nwwn; int /*<<< orphan*/  pbc_pwwn; } ;
struct bfi_iocfc_cfgrsp_s {TYPE_3__ pbc_cfg; } ;
struct bfi_faa_addr_msg_s {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct TYPE_5__ {TYPE_1__* attr; } ;
struct bfa_iocfc_s {struct bfi_iocfc_cfgrsp_s* cfgrsp; } ;
struct bfa_s {TYPE_2__ ioc; struct bfa_iocfc_s iocfc; } ;
struct TYPE_4__ {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCFC_E_CFG_DONE ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_iocfc_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocfc_process_faa_addr(struct bfa_s *bfa, struct bfi_faa_addr_msg_s *msg)
{
	struct bfa_iocfc_s		*iocfc   = &bfa->iocfc;
	struct bfi_iocfc_cfgrsp_s	*cfgrsp  = iocfc->cfgrsp;

	cfgrsp->pbc_cfg.pbc_pwwn = msg->pwwn;
	cfgrsp->pbc_cfg.pbc_nwwn = msg->nwwn;

	bfa->ioc.attr->pwwn = msg->pwwn;
	bfa->ioc.attr->nwwn = msg->nwwn;
	bfa_fsm_send_event(iocfc, IOCFC_E_CFG_DONE);
}