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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  enum pl330_cond { ____Placeholder_pl330_cond } pl330_cond ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;

/* Variables and functions */
 int ALWAYS ; 
 int BURST ; 
#define  DMA_DEV_TO_MEM 130 
#define  DMA_MEM_TO_DEV 129 
#define  DMA_MEM_TO_MEM 128 
 int SINGLE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _emit_ST (unsigned int,int /*<<< orphan*/ *,int) ; 
 int _emit_STP (unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 _emit_store(unsigned int dry_run, u8 buf[],
	enum pl330_cond cond, enum dma_transfer_direction direction,
	u8 peri)
{
	int off = 0;

	switch (direction) {
	case DMA_MEM_TO_MEM:
		/* fall through */
	case DMA_DEV_TO_MEM:
		off += _emit_ST(dry_run, &buf[off], cond);
		break;

	case DMA_MEM_TO_DEV:
		if (cond == ALWAYS) {
			off += _emit_STP(dry_run, &buf[off], SINGLE,
				peri);
			off += _emit_STP(dry_run, &buf[off], BURST,
				peri);
		} else {
			off += _emit_STP(dry_run, &buf[off], cond,
				peri);
		}
		break;

	default:
		/* this code should be unreachable */
		WARN_ON(1);
		break;
	}

	return off;
}