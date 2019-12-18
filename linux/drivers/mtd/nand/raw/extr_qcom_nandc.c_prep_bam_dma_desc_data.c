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
struct qcom_nand_controller {int /*<<< orphan*/  tx_chan; struct bam_transaction* bam_txn; } ;
struct bam_transaction {size_t rx_sgl_pos; size_t tx_sgl_pos; int /*<<< orphan*/ * data_sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 unsigned int NAND_BAM_NO_EOT ; 
 int prepare_bam_async_desc (struct qcom_nand_controller*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ *,void const*,int) ; 

__attribute__((used)) static int prep_bam_dma_desc_data(struct qcom_nand_controller *nandc, bool read,
				  const void *vaddr,
				  int size, unsigned int flags)
{
	int ret;
	struct bam_transaction *bam_txn = nandc->bam_txn;

	if (read) {
		sg_set_buf(&bam_txn->data_sgl[bam_txn->rx_sgl_pos],
			   vaddr, size);
		bam_txn->rx_sgl_pos++;
	} else {
		sg_set_buf(&bam_txn->data_sgl[bam_txn->tx_sgl_pos],
			   vaddr, size);
		bam_txn->tx_sgl_pos++;

		/*
		 * BAM will only set EOT for DMA_PREP_INTERRUPT so if this flag
		 * is not set, form the DMA descriptor
		 */
		if (!(flags & NAND_BAM_NO_EOT)) {
			ret = prepare_bam_async_desc(nandc, nandc->tx_chan,
						     DMA_PREP_INTERRUPT);
			if (ret)
				return ret;
		}
	}

	return 0;
}