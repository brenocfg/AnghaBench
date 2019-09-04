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
struct virt_dma_desc {int /*<<< orphan*/  tx; int /*<<< orphan*/  node; } ;
struct tegra_adma_chan_regs {int tc; int ctrl; int src_addr; int trg_addr; int fifo_ctrl; int config; } ;
struct tegra_adma_desc {struct tegra_adma_chan_regs ch_regs; } ;
struct tegra_adma_chan {struct tegra_adma_desc* desc; scalar_t__ tx_buf_count; scalar_t__ tx_buf_pos; int /*<<< orphan*/  vc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADMA_CH_CMD ; 
 int /*<<< orphan*/  ADMA_CH_CONFIG ; 
 int /*<<< orphan*/  ADMA_CH_CTRL ; 
 int /*<<< orphan*/  ADMA_CH_FIFO_CTRL ; 
 int /*<<< orphan*/  ADMA_CH_LOWER_SRC_ADDR ; 
 int /*<<< orphan*/  ADMA_CH_LOWER_TRG_ADDR ; 
 int /*<<< orphan*/  ADMA_CH_TC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_adma_chan*) ; 
 int /*<<< orphan*/  tdma_ch_write (struct tegra_adma_chan*,int /*<<< orphan*/ ,int) ; 
 struct tegra_adma_desc* to_tegra_adma_desc (int /*<<< orphan*/ *) ; 
 struct virt_dma_desc* vchan_next_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_adma_start(struct tegra_adma_chan *tdc)
{
	struct virt_dma_desc *vd = vchan_next_desc(&tdc->vc);
	struct tegra_adma_chan_regs *ch_regs;
	struct tegra_adma_desc *desc;

	if (!vd)
		return;

	list_del(&vd->node);

	desc = to_tegra_adma_desc(&vd->tx);

	if (!desc) {
		dev_warn(tdc2dev(tdc), "unable to start DMA, no descriptor\n");
		return;
	}

	ch_regs = &desc->ch_regs;

	tdc->tx_buf_pos = 0;
	tdc->tx_buf_count = 0;
	tdma_ch_write(tdc, ADMA_CH_TC, ch_regs->tc);
	tdma_ch_write(tdc, ADMA_CH_CTRL, ch_regs->ctrl);
	tdma_ch_write(tdc, ADMA_CH_LOWER_SRC_ADDR, ch_regs->src_addr);
	tdma_ch_write(tdc, ADMA_CH_LOWER_TRG_ADDR, ch_regs->trg_addr);
	tdma_ch_write(tdc, ADMA_CH_FIFO_CTRL, ch_regs->fifo_ctrl);
	tdma_ch_write(tdc, ADMA_CH_CONFIG, ch_regs->config);

	/* Start ADMA */
	tdma_ch_write(tdc, ADMA_CH_CMD, 1);

	tdc->desc = desc;
}