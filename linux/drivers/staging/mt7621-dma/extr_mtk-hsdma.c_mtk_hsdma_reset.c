#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mtk_hsdma_chan {TYPE_2__* rx_ring; TYPE_1__* tx_ring; } ;
struct mtk_hsdam_engine {int dummy; } ;
struct TYPE_4__ {scalar_t__ flags; scalar_t__ addr0; } ;
struct TYPE_3__ {int flags; scalar_t__ addr0; } ;

/* Variables and functions */
 int HSDMA_DESCS_NUM ; 
 int HSDMA_DESC_DONE ; 
 int HSDMA_DESC_LS0 ; 
 int /*<<< orphan*/  HSDMA_GLO_DEFAULT ; 
 int /*<<< orphan*/  HSDMA_INT_RX_Q0 ; 
 int /*<<< orphan*/  HSDMA_REG_GLO_CFG ; 
 int /*<<< orphan*/  HSDMA_REG_INT_MASK ; 
 int /*<<< orphan*/  mtk_hsdma_reset_chan (struct mtk_hsdam_engine*,struct mtk_hsdma_chan*) ; 
 int /*<<< orphan*/  mtk_hsdma_write (struct mtk_hsdam_engine*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hsdma_reset(struct mtk_hsdam_engine *hsdma,
			    struct mtk_hsdma_chan *chan)
{
	int i;

	/* disable dma */
	mtk_hsdma_write(hsdma, HSDMA_REG_GLO_CFG, 0);

	/* disable intr */
	mtk_hsdma_write(hsdma, HSDMA_REG_INT_MASK, 0);

	/* init desc value */
	for (i = 0; i < HSDMA_DESCS_NUM; i++) {
		chan->tx_ring[i].addr0 = 0;
		chan->tx_ring[i].flags = HSDMA_DESC_LS0 | HSDMA_DESC_DONE;
	}
	for (i = 0; i < HSDMA_DESCS_NUM; i++) {
		chan->rx_ring[i].addr0 = 0;
		chan->rx_ring[i].flags = 0;
	}

	/* reset */
	mtk_hsdma_reset_chan(hsdma, chan);

	/* enable intr */
	mtk_hsdma_write(hsdma, HSDMA_REG_INT_MASK, HSDMA_INT_RX_Q0);

	/* enable dma */
	mtk_hsdma_write(hsdma, HSDMA_REG_GLO_CFG, HSDMA_GLO_DEFAULT);
}