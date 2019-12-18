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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct bfa_cee_stats_s {int dummy; } ;
struct TYPE_4__ {int pa; int /*<<< orphan*/ * kva; } ;
struct TYPE_3__ {int pa; int /*<<< orphan*/ * kva; } ;
struct bfa_cee_s {struct bfa_cee_stats_s* stats; struct bfa_cee_attr_s* attr; TYPE_2__ stats_dma; TYPE_1__ attr_dma; } ;
struct bfa_cee_attr_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 int BFA_ROUNDUP (int,int /*<<< orphan*/ ) ; 

void
bfa_cee_mem_claim(struct bfa_cee_s *cee, u8 *dma_kva, u64 dma_pa)
{
	cee->attr_dma.kva = dma_kva;
	cee->attr_dma.pa = dma_pa;
	cee->stats_dma.kva = dma_kva + BFA_ROUNDUP(
			     sizeof(struct bfa_cee_attr_s), BFA_DMA_ALIGN_SZ);
	cee->stats_dma.pa = dma_pa + BFA_ROUNDUP(
			     sizeof(struct bfa_cee_attr_s), BFA_DMA_ALIGN_SZ);
	cee->attr = (struct bfa_cee_attr_s *) dma_kva;
	cee->stats = (struct bfa_cee_stats_s *) (dma_kva + BFA_ROUNDUP(
			sizeof(struct bfa_cee_attr_s), BFA_DMA_ALIGN_SZ));
}