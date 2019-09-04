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
struct TYPE_2__ {int /*<<< orphan*/  has_rwproof; } ;
struct atmel_mci {unsigned int buf_size; int buf_phys_addr; unsigned int data_size; int mode_reg; int /*<<< orphan*/  sg; TYPE_1__ caps; } ;
typedef  enum atmci_xfer_dir { ____Placeholder_atmci_xfer_dir } atmci_xfer_dir ;
typedef  enum atmci_pdc_buf { ____Placeholder_atmci_pdc_buf } atmci_pdc_buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATMCI_MR ; 
 int ATMCI_MR_PDCFBYTE ; 
 int /*<<< orphan*/  ATMEL_PDC_RCR ; 
 int /*<<< orphan*/  ATMEL_PDC_RPR ; 
 scalar_t__ ATMEL_PDC_SCND_BUF_OFF ; 
 int /*<<< orphan*/  ATMEL_PDC_TCR ; 
 int /*<<< orphan*/  ATMEL_PDC_TPR ; 
 int PDC_SECOND_BUF ; 
 int XFER_RECEIVE ; 
 int /*<<< orphan*/  atmci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int) ; 
 int sg_dma_address (int /*<<< orphan*/ ) ; 
 int sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_next (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmci_pdc_set_single_buf(struct atmel_mci *host,
	enum atmci_xfer_dir dir, enum atmci_pdc_buf buf_nb)
{
	u32 pointer_reg, counter_reg;
	unsigned int buf_size;

	if (dir == XFER_RECEIVE) {
		pointer_reg = ATMEL_PDC_RPR;
		counter_reg = ATMEL_PDC_RCR;
	} else {
		pointer_reg = ATMEL_PDC_TPR;
		counter_reg = ATMEL_PDC_TCR;
	}

	if (buf_nb == PDC_SECOND_BUF) {
		pointer_reg += ATMEL_PDC_SCND_BUF_OFF;
		counter_reg += ATMEL_PDC_SCND_BUF_OFF;
	}

	if (!host->caps.has_rwproof) {
		buf_size = host->buf_size;
		atmci_writel(host, pointer_reg, host->buf_phys_addr);
	} else {
		buf_size = sg_dma_len(host->sg);
		atmci_writel(host, pointer_reg, sg_dma_address(host->sg));
	}

	if (host->data_size <= buf_size) {
		if (host->data_size & 0x3) {
			/* If size is different from modulo 4, transfer bytes */
			atmci_writel(host, counter_reg, host->data_size);
			atmci_writel(host, ATMCI_MR, host->mode_reg | ATMCI_MR_PDCFBYTE);
		} else {
			/* Else transfer 32-bits words */
			atmci_writel(host, counter_reg, host->data_size / 4);
		}
		host->data_size = 0;
	} else {
		/* We assume the size of a page is 32-bits aligned */
		atmci_writel(host, counter_reg, sg_dma_len(host->sg) / 4);
		host->data_size -= sg_dma_len(host->sg);
		if (host->data_size)
			host->sg = sg_next(host->sg);
	}
}