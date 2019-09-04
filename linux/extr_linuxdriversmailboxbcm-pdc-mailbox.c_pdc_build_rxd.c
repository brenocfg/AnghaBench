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
typedef  int /*<<< orphan*/  u32 ;
struct pdc_state {size_t rxout; int /*<<< orphan*/  nrxpost; int /*<<< orphan*/  pdc_idx; struct dma64dd* rxd_64; TYPE_1__* pdev; } ;
struct dma64dd {void* ctrl2; void* ctrl1; void* addrhigh; void* addrlow; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t NEXTRXD (size_t,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
pdc_build_rxd(struct pdc_state *pdcs, dma_addr_t dma_addr,
	      u32 buf_len, u32 flags)
{
	struct device *dev = &pdcs->pdev->dev;
	struct dma64dd *rxd = &pdcs->rxd_64[pdcs->rxout];

	dev_dbg(dev,
		"Writing rx descriptor for PDC %u at index %u with length %u. flags %#x\n",
		pdcs->pdc_idx, pdcs->rxout, buf_len, flags);

	rxd->addrlow = cpu_to_le32(lower_32_bits(dma_addr));
	rxd->addrhigh = cpu_to_le32(upper_32_bits(dma_addr));
	rxd->ctrl1 = cpu_to_le32(flags);
	rxd->ctrl2 = cpu_to_le32(buf_len);

	/* bump ring index and return */
	pdcs->rxout = NEXTRXD(pdcs->rxout, pdcs->nrxpost);
}