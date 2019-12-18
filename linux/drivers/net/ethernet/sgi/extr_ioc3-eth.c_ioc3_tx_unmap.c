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
struct ioc3_private {int /*<<< orphan*/  dma_dev; struct ioc3_etxd* txr; } ;
struct ioc3_etxd {int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; int /*<<< orphan*/  bufcnt; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ETXD_B1CNT_MASK ; 
 int ETXD_B1CNT_SHIFT ; 
 int ETXD_B1V ; 
 int ETXD_B2CNT_MASK ; 
 int ETXD_B2CNT_SHIFT ; 
 int ETXD_B2V ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ioc3_tx_unmap(struct ioc3_private *ip, int entry)
{
	struct ioc3_etxd *desc;
	u32 cmd, bufcnt, len;

	desc = &ip->txr[entry];
	cmd = be32_to_cpu(desc->cmd);
	bufcnt = be32_to_cpu(desc->bufcnt);
	if (cmd & ETXD_B1V) {
		len = (bufcnt & ETXD_B1CNT_MASK) >> ETXD_B1CNT_SHIFT;
		dma_unmap_single(ip->dma_dev, be64_to_cpu(desc->p1),
				 len, DMA_TO_DEVICE);
	}
	if (cmd & ETXD_B2V) {
		len = (bufcnt & ETXD_B2CNT_MASK) >> ETXD_B2CNT_SHIFT;
		dma_unmap_single(ip->dma_dev, be64_to_cpu(desc->p2),
				 len, DMA_TO_DEVICE);
	}
}