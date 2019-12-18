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
struct ena_com_mmio_read {int /*<<< orphan*/ * read_resp; int /*<<< orphan*/  read_resp_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; scalar_t__ reg_bar; struct ena_com_mmio_read mmio_read; } ;

/* Variables and functions */
 scalar_t__ ENA_REGS_MMIO_RESP_HI_OFF ; 
 scalar_t__ ENA_REGS_MMIO_RESP_LO_OFF ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ena_com_mmio_reg_read_request_destroy(struct ena_com_dev *ena_dev)
{
	struct ena_com_mmio_read *mmio_read = &ena_dev->mmio_read;

	writel(0x0, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_LO_OFF);
	writel(0x0, ena_dev->reg_bar + ENA_REGS_MMIO_RESP_HI_OFF);

	dma_free_coherent(ena_dev->dmadev, sizeof(*mmio_read->read_resp),
			  mmio_read->read_resp, mmio_read->read_resp_dma_addr);

	mmio_read->read_resp = NULL;
}