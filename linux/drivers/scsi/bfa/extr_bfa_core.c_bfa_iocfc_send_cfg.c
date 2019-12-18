#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  coalesce; } ;
struct bfi_iocfc_cfg_s {int single_msix_vec; int num_cqs; TYPE_9__ intr_attr; void** rsp_cq_elems; int /*<<< orphan*/ * rsp_shadow_pi; int /*<<< orphan*/ * rsp_cq_ba; void** req_cq_elems; int /*<<< orphan*/ * req_shadow_ci; int /*<<< orphan*/ * req_cq_ba; int /*<<< orphan*/  cfgrsp_addr; void* num_fwtio_reqs; void* num_ioim_reqs; int /*<<< orphan*/  endian_sig; } ;
struct bfi_iocfc_cfg_req_s {int /*<<< orphan*/  ioc_cfg_dma_addr; int /*<<< orphan*/  mh; } ;
struct TYPE_12__ {int nvecs; } ;
struct TYPE_11__ {int /*<<< orphan*/  pa; } ;
struct TYPE_13__ {int /*<<< orphan*/  pa; } ;
struct TYPE_19__ {int /*<<< orphan*/  num_rspq_elems; int /*<<< orphan*/  num_reqq_elems; } ;
struct TYPE_14__ {int num_cqs; int /*<<< orphan*/  num_fwtio_reqs; int /*<<< orphan*/  num_ioim_reqs; } ;
struct bfa_iocfc_cfg_s {TYPE_8__ drvcfg; TYPE_3__ fwcfg; } ;
struct bfa_iocfc_s {TYPE_10__ cfg_info; TYPE_7__* rsp_cq_shadow_pi; TYPE_6__* rsp_cq_ba; TYPE_5__* req_cq_shadow_ci; TYPE_4__* req_cq_ba; TYPE_2__ cfgrsp_dma; struct bfa_iocfc_cfg_s cfg; struct bfi_iocfc_cfg_s* cfginfo; } ;
struct bfa_s {int /*<<< orphan*/  ioc; TYPE_1__ msix; struct bfa_iocfc_s iocfc; } ;
struct TYPE_18__ {int /*<<< orphan*/  pa; } ;
struct TYPE_17__ {int /*<<< orphan*/  pa; } ;
struct TYPE_16__ {int /*<<< orphan*/  pa; } ;
struct TYPE_15__ {int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  BFI_IOCFC_H2I_CFG_REQ ; 
 int /*<<< orphan*/  BFI_IOC_ENDIAN_SIG ; 
 int BFI_IOC_MAX_CQS ; 
 int /*<<< orphan*/  BFI_MC_IOCFC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_dma_be_addr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcpim_get_throttle_cfg (struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fn_lpu (struct bfa_s*) ; 
 scalar_t__ bfa_fsm_cmp_state (struct bfa_iocfc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_send (int /*<<< orphan*/ *,struct bfi_iocfc_cfg_req_s*,int) ; 
 int /*<<< orphan*/  bfa_iocfc_reset_queues (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_iocfc_sm_init_cfg_wait ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocfc_send_cfg(void *bfa_arg)
{
	struct bfa_s *bfa = bfa_arg;
	struct bfa_iocfc_s *iocfc = &bfa->iocfc;
	struct bfi_iocfc_cfg_req_s cfg_req;
	struct bfi_iocfc_cfg_s *cfg_info = iocfc->cfginfo;
	struct bfa_iocfc_cfg_s	*cfg = &iocfc->cfg;
	int		i;

	WARN_ON(cfg->fwcfg.num_cqs > BFI_IOC_MAX_CQS);
	bfa_trc(bfa, cfg->fwcfg.num_cqs);

	bfa_iocfc_reset_queues(bfa);

	/*
	 * initialize IOC configuration info
	 */
	cfg_info->single_msix_vec = 0;
	if (bfa->msix.nvecs == 1)
		cfg_info->single_msix_vec = 1;
	cfg_info->endian_sig = BFI_IOC_ENDIAN_SIG;
	cfg_info->num_cqs = cfg->fwcfg.num_cqs;
	cfg_info->num_ioim_reqs = cpu_to_be16(bfa_fcpim_get_throttle_cfg(bfa,
					       cfg->fwcfg.num_ioim_reqs));
	cfg_info->num_fwtio_reqs = cpu_to_be16(cfg->fwcfg.num_fwtio_reqs);

	bfa_dma_be_addr_set(cfg_info->cfgrsp_addr, iocfc->cfgrsp_dma.pa);
	/*
	 * dma map REQ and RSP circular queues and shadow pointers
	 */
	for (i = 0; i < cfg->fwcfg.num_cqs; i++) {
		bfa_dma_be_addr_set(cfg_info->req_cq_ba[i],
				    iocfc->req_cq_ba[i].pa);
		bfa_dma_be_addr_set(cfg_info->req_shadow_ci[i],
				    iocfc->req_cq_shadow_ci[i].pa);
		cfg_info->req_cq_elems[i] =
			cpu_to_be16(cfg->drvcfg.num_reqq_elems);

		bfa_dma_be_addr_set(cfg_info->rsp_cq_ba[i],
				    iocfc->rsp_cq_ba[i].pa);
		bfa_dma_be_addr_set(cfg_info->rsp_shadow_pi[i],
				    iocfc->rsp_cq_shadow_pi[i].pa);
		cfg_info->rsp_cq_elems[i] =
			cpu_to_be16(cfg->drvcfg.num_rspq_elems);
	}

	/*
	 * Enable interrupt coalescing if it is driver init path
	 * and not ioc disable/enable path.
	 */
	if (bfa_fsm_cmp_state(iocfc, bfa_iocfc_sm_init_cfg_wait))
		cfg_info->intr_attr.coalesce = BFA_TRUE;

	/*
	 * dma map IOC configuration itself
	 */
	bfi_h2i_set(cfg_req.mh, BFI_MC_IOCFC, BFI_IOCFC_H2I_CFG_REQ,
		    bfa_fn_lpu(bfa));
	bfa_dma_be_addr_set(cfg_req.ioc_cfg_dma_addr, iocfc->cfg_info.pa);

	bfa_ioc_mbox_send(&bfa->ioc, &cfg_req,
			  sizeof(struct bfi_iocfc_cfg_req_s));
}