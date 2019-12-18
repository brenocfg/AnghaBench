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
struct mtk_hsdma_chan {int tx_idx; int rx_idx; int id; } ;
struct mtk_hsdam_engine {int dummy; } ;

/* Variables and functions */
 int HSDMA_DESCS_NUM ; 
 int /*<<< orphan*/  HSDMA_REG_RST_CFG ; 
 int /*<<< orphan*/  HSDMA_REG_RX_CRX ; 
 int /*<<< orphan*/  HSDMA_REG_TX_CTX ; 
 int HSDMA_RST_RX_SHIFT ; 
 int HSDMA_RST_TX_SHIFT ; 
 int /*<<< orphan*/  mtk_hsdma_write (struct mtk_hsdam_engine*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mtk_hsdma_reset_chan(struct mtk_hsdam_engine *hsdma,
				 struct mtk_hsdma_chan *chan)
{
	chan->tx_idx = 0;
	chan->rx_idx = HSDMA_DESCS_NUM - 1;

	mtk_hsdma_write(hsdma, HSDMA_REG_TX_CTX, chan->tx_idx);
	mtk_hsdma_write(hsdma, HSDMA_REG_RX_CRX, chan->rx_idx);

	mtk_hsdma_write(hsdma, HSDMA_REG_RST_CFG,
			0x1 << (chan->id + HSDMA_RST_TX_SHIFT));
	mtk_hsdma_write(hsdma, HSDMA_REG_RST_CFG,
			0x1 << (chan->id + HSDMA_RST_RX_SHIFT));
}