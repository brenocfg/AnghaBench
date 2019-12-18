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
typedef  scalar_t__ uint ;
typedef  int u16 ;
struct dma_info {scalar_t__ ntxd; scalar_t__ nrxd; int dmadesc_align; scalar_t__ rxdalloc; scalar_t__ rxdalign; scalar_t__ rxdpaorig; scalar_t__ rxdpa; struct dma64desc* rxd64; int /*<<< orphan*/  name; int /*<<< orphan*/  core; scalar_t__ txdalloc; scalar_t__ txdalign; scalar_t__ txdpaorig; scalar_t__ txdpa; struct dma64desc* txd64; } ;
struct dma64desc {int dummy; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  D64RINGALIGN ; 
 scalar_t__ DMA_TX ; 
 int /*<<< orphan*/  brcms_dbg_dma (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* dma_ringalloc (struct dma_info*,int /*<<< orphan*/ ,int,int*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ roundup (unsigned long,int) ; 

__attribute__((used)) static bool dma64_alloc(struct dma_info *di, uint direction)
{
	u16 size;
	uint ddlen;
	void *va;
	uint alloced = 0;
	u16 align;
	u16 align_bits;

	ddlen = sizeof(struct dma64desc);

	size = (direction == DMA_TX) ? (di->ntxd * ddlen) : (di->nrxd * ddlen);
	align_bits = di->dmadesc_align;
	align = (1 << align_bits);

	if (direction == DMA_TX) {
		va = dma_ringalloc(di, D64RINGALIGN, size, &align_bits,
			&alloced, &di->txdpaorig);
		if (va == NULL) {
			brcms_dbg_dma(di->core,
				      "%s: DMA_ALLOC_CONSISTENT(ntxd) failed\n",
				      di->name);
			return false;
		}
		align = (1 << align_bits);
		di->txd64 = (struct dma64desc *)
					roundup((unsigned long)va, align);
		di->txdalign = (uint) ((s8 *)di->txd64 - (s8 *) va);
		di->txdpa = di->txdpaorig + di->txdalign;
		di->txdalloc = alloced;
	} else {
		va = dma_ringalloc(di, D64RINGALIGN, size, &align_bits,
			&alloced, &di->rxdpaorig);
		if (va == NULL) {
			brcms_dbg_dma(di->core,
				      "%s: DMA_ALLOC_CONSISTENT(nrxd) failed\n",
				      di->name);
			return false;
		}
		align = (1 << align_bits);
		di->rxd64 = (struct dma64desc *)
					roundup((unsigned long)va, align);
		di->rxdalign = (uint) ((s8 *)di->rxd64 - (s8 *) va);
		di->rxdpa = di->rxdpaorig + di->rxdalign;
		di->rxdalloc = alloced;
	}

	return true;
}