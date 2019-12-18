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
typedef  int u32 ;
struct bfi_diag_fwping_req_s {int data; int /*<<< orphan*/  mh; int /*<<< orphan*/  count; int /*<<< orphan*/  alen; } ;
struct TYPE_4__ {scalar_t__ msg; } ;
struct TYPE_3__ {int data; TYPE_2__ mbcmd; int /*<<< orphan*/  count; int /*<<< orphan*/  dbuf_pa; scalar_t__ dbuf_kva; } ;
struct bfa_diag_s {TYPE_1__ fwping; int /*<<< orphan*/  ioc; } ;

/* Variables and functions */
 int BFI_DIAG_DMA_BUF_SZ ; 
 int /*<<< orphan*/  BFI_DIAG_H2I_FWPING ; 
 int /*<<< orphan*/  BFI_MC_DIAG ; 
 int /*<<< orphan*/  bfa_alen_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_mbox_queue (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_portid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_diag_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
diag_fwping_send(struct bfa_diag_s *diag)
{
	struct bfi_diag_fwping_req_s *fwping_req;
	u32	i;

	bfa_trc(diag, diag->fwping.dbuf_pa);

	/* fill DMA area with pattern */
	for (i = 0; i < (BFI_DIAG_DMA_BUF_SZ >> 2); i++)
		*((u32 *)diag->fwping.dbuf_kva + i) = diag->fwping.data;

	/* Fill mbox msg */
	fwping_req = (struct bfi_diag_fwping_req_s *)diag->fwping.mbcmd.msg;

	/* Setup SG list */
	bfa_alen_set(&fwping_req->alen, BFI_DIAG_DMA_BUF_SZ,
			diag->fwping.dbuf_pa);
	/* Set up dma count */
	fwping_req->count = cpu_to_be32(diag->fwping.count);
	/* Set up data pattern */
	fwping_req->data = diag->fwping.data;

	/* build host command */
	bfi_h2i_set(fwping_req->mh, BFI_MC_DIAG, BFI_DIAG_H2I_FWPING,
		bfa_ioc_portid(diag->ioc));

	/* send mbox cmd */
	bfa_ioc_mbox_queue(diag->ioc, &diag->fwping.mbcmd);
}