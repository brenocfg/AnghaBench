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
struct mtk_hsdma_chan {int dummy; } ;
struct mtk_hsdam_engine {struct mtk_hsdma_chan* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSDMA_REG_GLO_CFG ; 
 int /*<<< orphan*/  HSDMA_REG_INT_MASK ; 
 int /*<<< orphan*/  HSDMA_REG_RX_BASE ; 
 int /*<<< orphan*/  HSDMA_REG_RX_CNT ; 
 int /*<<< orphan*/  HSDMA_REG_TX_BASE ; 
 int /*<<< orphan*/  HSDMA_REG_TX_CNT ; 
 int /*<<< orphan*/  mtk_hsdam_free_desc (struct mtk_hsdam_engine*,struct mtk_hsdma_chan*) ; 
 int /*<<< orphan*/  mtk_hsdma_reset_chan (struct mtk_hsdam_engine*,struct mtk_hsdma_chan*) ; 
 int /*<<< orphan*/  mtk_hsdma_write (struct mtk_hsdam_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hsdma_uninit(struct mtk_hsdam_engine *hsdma)
{
	struct mtk_hsdma_chan *chan;

	/* disable dma */
	mtk_hsdma_write(hsdma, HSDMA_REG_GLO_CFG, 0);

	/* disable intr */
	mtk_hsdma_write(hsdma, HSDMA_REG_INT_MASK, 0);

	/* free desc */
	chan = &hsdma->chan[0];
	mtk_hsdam_free_desc(hsdma, chan);

	/* tx */
	mtk_hsdma_write(hsdma, HSDMA_REG_TX_BASE, 0);
	mtk_hsdma_write(hsdma, HSDMA_REG_TX_CNT, 0);
	/* rx */
	mtk_hsdma_write(hsdma, HSDMA_REG_RX_BASE, 0);
	mtk_hsdma_write(hsdma, HSDMA_REG_RX_CNT, 0);
	/* reset */
	mtk_hsdma_reset_chan(hsdma, chan);
}