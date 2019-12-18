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
struct pch_spi_dma_ctrl {void* rx_buf_virt; int /*<<< orphan*/  rx_buf_dma; void* tx_buf_virt; int /*<<< orphan*/  tx_buf_dma; } ;
struct pch_spi_data {struct pch_spi_dma_ctrl dma; } ;
struct pch_spi_board_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCH_BUF_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pch_alloc_dma_buf(struct pch_spi_board_data *board_dat,
			      struct pch_spi_data *data)
{
	struct pch_spi_dma_ctrl *dma;
	int ret;

	dma = &data->dma;
	ret = 0;
	/* Get Consistent memory for Tx DMA */
	dma->tx_buf_virt = dma_alloc_coherent(&board_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->tx_buf_dma, GFP_KERNEL);
	if (!dma->tx_buf_virt)
		ret = -ENOMEM;

	/* Get Consistent memory for Rx DMA */
	dma->rx_buf_virt = dma_alloc_coherent(&board_dat->pdev->dev,
				PCH_BUF_SIZE, &dma->rx_buf_dma, GFP_KERNEL);
	if (!dma->rx_buf_virt)
		ret = -ENOMEM;

	return ret;
}