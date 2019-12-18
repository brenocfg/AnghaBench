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
struct bfa_fru_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 struct bfa_fru_s* BFA_FRU (struct bfa_s*) ; 
 struct bfa_mem_dma_s* BFA_MEM_FRU_DMA (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fru_attach (struct bfa_fru_s*,int /*<<< orphan*/ *,struct bfa_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fru_memclaim (struct bfa_fru_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_com_fru_attach(struct bfa_s *bfa, bfa_boolean_t mincfg)
{
	struct bfa_fru_s	*fru = BFA_FRU(bfa);
	struct bfa_mem_dma_s	*fru_dma = BFA_MEM_FRU_DMA(bfa);

	bfa_fru_attach(fru, &bfa->ioc, bfa, bfa->trcmod, mincfg);
	bfa_fru_memclaim(fru, fru_dma->kva_curp, fru_dma->dma_curp, mincfg);
}