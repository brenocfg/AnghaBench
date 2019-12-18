#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  int u32 ;
struct TYPE_2__ {int dmactrlflags; } ;
struct dma_info {scalar_t__ dataoffsetlow; int dataoffsethigh; TYPE_1__ dma; } ;
struct dma64desc {void* ctrl2; void* ctrl1; void* addrhigh; void* addrlow; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int D64_CTRL2_AE ; 
 int D64_CTRL2_AE_SHIFT ; 
 int D64_CTRL2_BC_MASK ; 
 int D64_CTRL2_PARITY ; 
 int DMA_CTRL_PEN ; 
 int PCI32ADDR_HIGH ; 
 int PCI32ADDR_HIGH_SHIFT ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ dma64_dd_parity (struct dma64desc*) ; 

__attribute__((used)) static inline void
dma64_dd_upd(struct dma_info *di, struct dma64desc *ddring,
	     dma_addr_t pa, uint outidx, u32 *flags, u32 bufcount)
{
	u32 ctrl2 = bufcount & D64_CTRL2_BC_MASK;

	/* PCI bus with big(>1G) physical address, use address extension */
	if ((di->dataoffsetlow == 0) || !(pa & PCI32ADDR_HIGH)) {
		ddring[outidx].addrlow = cpu_to_le32(pa + di->dataoffsetlow);
		ddring[outidx].addrhigh = cpu_to_le32(di->dataoffsethigh);
		ddring[outidx].ctrl1 = cpu_to_le32(*flags);
		ddring[outidx].ctrl2 = cpu_to_le32(ctrl2);
	} else {
		/* address extension for 32-bit PCI */
		u32 ae;

		ae = (pa & PCI32ADDR_HIGH) >> PCI32ADDR_HIGH_SHIFT;
		pa &= ~PCI32ADDR_HIGH;

		ctrl2 |= (ae << D64_CTRL2_AE_SHIFT) & D64_CTRL2_AE;
		ddring[outidx].addrlow = cpu_to_le32(pa + di->dataoffsetlow);
		ddring[outidx].addrhigh = cpu_to_le32(di->dataoffsethigh);
		ddring[outidx].ctrl1 = cpu_to_le32(*flags);
		ddring[outidx].ctrl2 = cpu_to_le32(ctrl2);
	}
	if (di->dma.dmactrlflags & DMA_CTRL_PEN) {
		if (dma64_dd_parity(&ddring[outidx]))
			ddring[outidx].ctrl2 =
			     cpu_to_le32(ctrl2 | D64_CTRL2_PARITY);
	}
}