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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {TYPE_1__* mdl; } ;
struct TYPE_6__ {TYPE_2__ mem_info; } ;
struct bna_res_info {TYPE_3__ res_u; } ;
struct bna_ioceth {int /*<<< orphan*/ * stop_cbarg; int /*<<< orphan*/ * stop_cbfn; int /*<<< orphan*/  ioc; struct bna* bna; } ;
struct bna {int /*<<< orphan*/  msgq; int /*<<< orphan*/  flash; int /*<<< orphan*/  cee; int /*<<< orphan*/  pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * kva; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_MC_ENET ; 
 int /*<<< orphan*/  BFI_PCIFN_CLASS_ETH ; 
 int /*<<< orphan*/  BNA_GET_DMA_ADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t BNA_RES_MEM_T_ATTR ; 
 size_t BNA_RES_MEM_T_COM ; 
 size_t BNA_RES_MEM_T_FWTRC ; 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_ioceth*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_msgq_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_msgq_memclaim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_msgq_meminfo () ; 
 int /*<<< orphan*/  bfa_msgq_regisr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bna*) ; 
 int /*<<< orphan*/  bfa_nw_cee_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bna*) ; 
 int /*<<< orphan*/  bfa_nw_cee_mem_claim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_nw_cee_meminfo () ; 
 int /*<<< orphan*/  bfa_nw_flash_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bna*) ; 
 int /*<<< orphan*/  bfa_nw_flash_memclaim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_nw_flash_meminfo () ; 
 int /*<<< orphan*/  bfa_nw_ioc_attach (int /*<<< orphan*/ *,struct bna_ioceth*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_nw_ioc_debug_memclaim (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mem_claim (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_pci_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_attr_init (struct bna_ioceth*) ; 
 int /*<<< orphan*/  bna_ioceth_cbfn ; 
 int /*<<< orphan*/  bna_ioceth_sm_stopped ; 
 int /*<<< orphan*/  bna_msgq_rsp_handler ; 

__attribute__((used)) static void
bna_ioceth_init(struct bna_ioceth *ioceth, struct bna *bna,
		struct bna_res_info *res_info)
{
	u64 dma;
	u8 *kva;

	ioceth->bna = bna;

	/**
	 * Attach IOC and claim:
	 *	1. DMA memory for IOC attributes
	 *	2. Kernel memory for FW trace
	 */
	bfa_nw_ioc_attach(&ioceth->ioc, ioceth, &bna_ioceth_cbfn);
	bfa_nw_ioc_pci_init(&ioceth->ioc, &bna->pcidev, BFI_PCIFN_CLASS_ETH);

	BNA_GET_DMA_ADDR(
		&res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.mdl[0].dma, dma);
	kva = res_info[BNA_RES_MEM_T_ATTR].res_u.mem_info.mdl[0].kva;
	bfa_nw_ioc_mem_claim(&ioceth->ioc, kva, dma);

	kva = res_info[BNA_RES_MEM_T_FWTRC].res_u.mem_info.mdl[0].kva;
	bfa_nw_ioc_debug_memclaim(&ioceth->ioc, kva);

	/**
	 * Attach common modules (Diag, SFP, CEE, Port) and claim respective
	 * DMA memory.
	 */
	BNA_GET_DMA_ADDR(
		&res_info[BNA_RES_MEM_T_COM].res_u.mem_info.mdl[0].dma, dma);
	kva = res_info[BNA_RES_MEM_T_COM].res_u.mem_info.mdl[0].kva;
	bfa_nw_cee_attach(&bna->cee, &ioceth->ioc, bna);
	bfa_nw_cee_mem_claim(&bna->cee, kva, dma);
	kva += bfa_nw_cee_meminfo();
	dma += bfa_nw_cee_meminfo();

	bfa_nw_flash_attach(&bna->flash, &ioceth->ioc, bna);
	bfa_nw_flash_memclaim(&bna->flash, kva, dma);
	kva += bfa_nw_flash_meminfo();
	dma += bfa_nw_flash_meminfo();

	bfa_msgq_attach(&bna->msgq, &ioceth->ioc);
	bfa_msgq_memclaim(&bna->msgq, kva, dma);
	bfa_msgq_regisr(&bna->msgq, BFI_MC_ENET, bna_msgq_rsp_handler, bna);
	kva += bfa_msgq_meminfo();
	dma += bfa_msgq_meminfo();

	ioceth->stop_cbfn = NULL;
	ioceth->stop_cbarg = NULL;

	bna_attr_init(ioceth);

	bfa_fsm_set_state(ioceth, bna_ioceth_sm_stopped);
}