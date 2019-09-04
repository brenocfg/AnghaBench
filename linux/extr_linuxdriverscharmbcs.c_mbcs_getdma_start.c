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
union cm_control {int rd_dma_go; int /*<<< orphan*/  cm_control_reg; } ;
typedef  int uint64_t ;
struct getdma {int bytes; scalar_t__ localAddr; int /*<<< orphan*/  intrVector; int /*<<< orphan*/  intrHostDest; int /*<<< orphan*/  amoModType; int /*<<< orphan*/  amoHostDest; int /*<<< orphan*/  peerIO; int /*<<< orphan*/  DoneIntEnable; int /*<<< orphan*/  DoneAmoEnable; int /*<<< orphan*/  hostAddr; } ;
struct mbcs_soft {struct getdma getdma; void* mmr_base; } ;

/* Variables and functions */
 scalar_t__ MB2 ; 
 scalar_t__ MB4 ; 
 scalar_t__ MB6 ; 
 int MBCS_CACHELINE_SIZE ; 
 int /*<<< orphan*/  MBCS_CM_CONTROL ; 
 int /*<<< orphan*/  MBCS_MMR_GET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBCS_MMR_SET (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbcs_getdma_set (void*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiocx_dma_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mbcs_getdma_start(struct mbcs_soft *soft)
{
	void *mmr_base;
	struct getdma *gdma;
	uint64_t numPkts;
	union cm_control cm_control;

	mmr_base = soft->mmr_base;
	gdma = &soft->getdma;

	/* check that host address got setup */
	if (!gdma->hostAddr)
		return -1;

	numPkts =
	    (gdma->bytes + (MBCS_CACHELINE_SIZE - 1)) / MBCS_CACHELINE_SIZE;

	/* program engine */
	mbcs_getdma_set(mmr_base, tiocx_dma_addr(gdma->hostAddr),
		   gdma->localAddr,
		   (gdma->localAddr < MB2) ? 0 :
		   (gdma->localAddr < MB4) ? 1 :
		   (gdma->localAddr < MB6) ? 2 : 3,
		   numPkts,
		   gdma->DoneAmoEnable,
		   gdma->DoneIntEnable,
		   gdma->peerIO,
		   gdma->amoHostDest,
		   gdma->amoModType,
		   gdma->intrHostDest, gdma->intrVector);

	/* start engine */
	cm_control.cm_control_reg = MBCS_MMR_GET(mmr_base, MBCS_CM_CONTROL);
	cm_control.rd_dma_go = 1;
	MBCS_MMR_SET(mmr_base, MBCS_CM_CONTROL, cm_control.cm_control_reg);

	return 0;

}