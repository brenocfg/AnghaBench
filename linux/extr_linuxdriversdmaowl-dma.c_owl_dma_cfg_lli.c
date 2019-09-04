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
typedef  int u32 ;
struct owl_dma_vchan {int dummy; } ;
struct owl_dma_lli_hw {int fcnt; int flen; int /*<<< orphan*/  ctrlb; int /*<<< orphan*/  ctrla; scalar_t__ dst_stride; scalar_t__ src_stride; void* daddr; void* saddr; scalar_t__ next_lli; } ;
struct owl_dma_lli {struct owl_dma_lli_hw hw; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  void* dma_addr_t ;

/* Variables and functions */
#define  DMA_MEM_TO_MEM 128 
 int EINVAL ; 
 int /*<<< orphan*/  OWL_DMA_INTCTL_SUPER_BLOCK ; 
 int OWL_DMA_LLC_DAV_LOAD_NEXT ; 
 int OWL_DMA_LLC_SAV_LOAD_NEXT ; 
 int OWL_DMA_MODE_DAM_INC ; 
 int OWL_DMA_MODE_DT_DCU ; 
 int OWL_DMA_MODE_PW (int /*<<< orphan*/ ) ; 
 int OWL_DMA_MODE_SAM_INC ; 
 int OWL_DMA_MODE_ST_DCU ; 
 int OWL_DMA_MODE_TS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llc_hw_ctrla (int,int) ; 
 int /*<<< orphan*/  llc_hw_ctrlb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int owl_dma_cfg_lli(struct owl_dma_vchan *vchan,
				  struct owl_dma_lli *lli,
				  dma_addr_t src, dma_addr_t dst,
				  u32 len, enum dma_transfer_direction dir)
{
	struct owl_dma_lli_hw *hw = &lli->hw;
	u32 mode;

	mode = OWL_DMA_MODE_PW(0);

	switch (dir) {
	case DMA_MEM_TO_MEM:
		mode |= OWL_DMA_MODE_TS(0) | OWL_DMA_MODE_ST_DCU |
			OWL_DMA_MODE_DT_DCU | OWL_DMA_MODE_SAM_INC |
			OWL_DMA_MODE_DAM_INC;

		break;
	default:
		return -EINVAL;
	}

	hw->next_lli = 0; /* One link list by default */
	hw->saddr = src;
	hw->daddr = dst;

	hw->fcnt = 1; /* Frame count fixed as 1 */
	hw->flen = len; /* Max frame length is 1MB */
	hw->src_stride = 0;
	hw->dst_stride = 0;
	hw->ctrla = llc_hw_ctrla(mode,
				 OWL_DMA_LLC_SAV_LOAD_NEXT |
				 OWL_DMA_LLC_DAV_LOAD_NEXT);

	hw->ctrlb = llc_hw_ctrlb(OWL_DMA_INTCTL_SUPER_BLOCK);

	return 0;
}