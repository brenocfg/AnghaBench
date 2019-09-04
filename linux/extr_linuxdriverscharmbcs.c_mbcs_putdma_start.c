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
union cm_control {int wr_dma_go; int /*<<< orphan*/  cm_control_reg; } ;
typedef  int uint64_t ;
struct putdma {int bytes; scalar_t__ localAddr; int /*<<< orphan*/  intrVector; int /*<<< orphan*/  intrHostDest; int /*<<< orphan*/  amoModType; int /*<<< orphan*/  amoHostDest; int /*<<< orphan*/  peerIO; int /*<<< orphan*/  DoneIntEnable; int /*<<< orphan*/  DoneAmoEnable; int /*<<< orphan*/  hostAddr; } ;
struct mbcs_soft {struct putdma putdma; void* mmr_base; } ;

/* Variables and functions */
 scalar_t__ MB2 ; 
 scalar_t__ MB4 ; 
 scalar_t__ MB6 ; 
 int MBCS_CACHELINE_SIZE ; 
 int /*<<< orphan*/  MBCS_CM_CONTROL ; 
 int /*<<< orphan*/  MBCS_MMR_GET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBCS_MMR_SET (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbcs_putdma_set (void*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiocx_dma_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mbcs_putdma_start(struct mbcs_soft *soft)
{
	void *mmr_base;
	struct putdma *pdma;
	uint64_t numPkts;
	union cm_control cm_control;

	mmr_base = soft->mmr_base;
	pdma = &soft->putdma;

	/* check that host address got setup */
	if (!pdma->hostAddr)
		return -1;

	numPkts =
	    (pdma->bytes + (MBCS_CACHELINE_SIZE - 1)) / MBCS_CACHELINE_SIZE;

	/* program engine */
	mbcs_putdma_set(mmr_base, tiocx_dma_addr(pdma->hostAddr),
		   pdma->localAddr,
		   (pdma->localAddr < MB2) ? 0 :
		   (pdma->localAddr < MB4) ? 1 :
		   (pdma->localAddr < MB6) ? 2 : 3,
		   numPkts,
		   pdma->DoneAmoEnable,
		   pdma->DoneIntEnable,
		   pdma->peerIO,
		   pdma->amoHostDest,
		   pdma->amoModType,
		   pdma->intrHostDest, pdma->intrVector);

	/* start engine */
	cm_control.cm_control_reg = MBCS_MMR_GET(mmr_base, MBCS_CM_CONTROL);
	cm_control.wr_dma_go = 1;
	MBCS_MMR_SET(mmr_base, MBCS_CM_CONTROL, cm_control.cm_control_reg);

	return 0;

}