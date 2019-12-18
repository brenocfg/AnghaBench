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
struct TYPE_6__ {scalar_t__ pbc_pwwn; int /*<<< orphan*/  pbc_nwwn; } ;
struct bfa_iocfc_fwcfg_s {void* num_rports; void* num_uf_bufs; void* num_fcxp_reqs; void* num_tskim_reqs; void* num_fwtio_reqs; void* num_ioim_reqs; int /*<<< orphan*/  num_cqs; } ;
struct bfi_iocfc_cfgrsp_s {TYPE_3__ pbc_cfg; int /*<<< orphan*/  qreg; struct bfa_iocfc_fwcfg_s fwcfg; } ;
struct bfa_iocfc_s {struct bfi_iocfc_cfgrsp_s* cfgrsp; } ;
struct TYPE_5__ {TYPE_1__* attr; } ;
struct bfa_s {struct bfa_iocfc_s iocfc; TYPE_2__ ioc; } ;
struct TYPE_4__ {scalar_t__ pwwn; int /*<<< orphan*/  nwwn; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCFC_E_CFG_DONE ; 
 void* be16_to_cpu (void*) ; 
 int /*<<< orphan*/  bfa_fsm_send_event (struct bfa_iocfc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_iocfc_qreg (struct bfa_s*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_iocfc_res_recfg (struct bfa_s*,struct bfa_iocfc_fwcfg_s*) ; 
 int /*<<< orphan*/  bfa_msix_queue_install (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_cfgrsp(struct bfa_s *bfa)
{
	struct bfa_iocfc_s		*iocfc	 = &bfa->iocfc;
	struct bfi_iocfc_cfgrsp_s	*cfgrsp	 = iocfc->cfgrsp;
	struct bfa_iocfc_fwcfg_s	*fwcfg	 = &cfgrsp->fwcfg;

	fwcfg->num_cqs	      = fwcfg->num_cqs;
	fwcfg->num_ioim_reqs  = be16_to_cpu(fwcfg->num_ioim_reqs);
	fwcfg->num_fwtio_reqs = be16_to_cpu(fwcfg->num_fwtio_reqs);
	fwcfg->num_tskim_reqs = be16_to_cpu(fwcfg->num_tskim_reqs);
	fwcfg->num_fcxp_reqs  = be16_to_cpu(fwcfg->num_fcxp_reqs);
	fwcfg->num_uf_bufs    = be16_to_cpu(fwcfg->num_uf_bufs);
	fwcfg->num_rports     = be16_to_cpu(fwcfg->num_rports);

	/*
	 * configure queue register offsets as learnt from firmware
	 */
	bfa_iocfc_qreg(bfa, &cfgrsp->qreg);

	/*
	 * Re-configure resources as learnt from Firmware
	 */
	bfa_iocfc_res_recfg(bfa, fwcfg);

	/*
	 * Install MSIX queue handlers
	 */
	bfa_msix_queue_install(bfa);

	if (bfa->iocfc.cfgrsp->pbc_cfg.pbc_pwwn != 0) {
		bfa->ioc.attr->pwwn = bfa->iocfc.cfgrsp->pbc_cfg.pbc_pwwn;
		bfa->ioc.attr->nwwn = bfa->iocfc.cfgrsp->pbc_cfg.pbc_nwwn;
		bfa_fsm_send_event(iocfc, IOCFC_E_CFG_DONE);
	}
}