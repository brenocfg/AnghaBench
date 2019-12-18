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
struct bfa_s {int /*<<< orphan*/  trcmod; int /*<<< orphan*/  ioc; } ;
struct bfa_mem_dma_s {int /*<<< orphan*/  dma_curp; int /*<<< orphan*/  kva_curp; } ;
struct bfa_diag_s {int dummy; } ;

/* Variables and functions */
 struct bfa_diag_s* BFA_DIAG_MOD (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_DIAG_DMA (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_diag_attach (struct bfa_diag_s*,int /*<<< orphan*/ *,struct bfa_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_diag_memclaim (struct bfa_diag_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcport_beacon ; 

__attribute__((used)) static void
bfa_com_diag_attach(struct bfa_s *bfa)
{
	struct bfa_diag_s	*diag = BFA_DIAG_MOD(bfa);
	struct bfa_mem_dma_s	*diag_dma = BFA_MEM_DIAG_DMA(bfa);

	bfa_diag_attach(diag, &bfa->ioc, bfa, bfa_fcport_beacon, bfa->trcmod);
	bfa_diag_memclaim(diag, diag_dma->kva_curp, diag_dma->dma_curp);
}