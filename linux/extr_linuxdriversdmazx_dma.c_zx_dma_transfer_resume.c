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
struct zx_dma_chan {TYPE_1__* phy; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_ZX_CTRL ; 
 int /*<<< orphan*/  ZX_CH_ENABLE ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 struct zx_dma_chan* to_zx_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int zx_dma_transfer_resume(struct dma_chan *chan)
{
	struct zx_dma_chan *c = to_zx_chan(chan);
	u32 val = 0;

	val = readl_relaxed(c->phy->base + REG_ZX_CTRL);
	val |= ZX_CH_ENABLE;
	writel_relaxed(val, c->phy->base + REG_ZX_CTRL);

	return 0;
}