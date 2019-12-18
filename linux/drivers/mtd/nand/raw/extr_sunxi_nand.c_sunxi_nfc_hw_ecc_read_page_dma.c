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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  steps; } ;
struct nand_chip {TYPE_1__ ecc; int /*<<< orphan*/  cur_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sunxi_nfc_hw_ecc_read_chunks_dma (struct nand_chip*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int sunxi_nfc_hw_ecc_read_page (struct nand_chip*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sunxi_nfc_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_page_dma(struct nand_chip *nand, u8 *buf,
					  int oob_required, int page)
{
	int ret;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_read_page_op(nand, page, 0, NULL, 0);

	ret = sunxi_nfc_hw_ecc_read_chunks_dma(nand, buf, oob_required, page,
					       nand->ecc.steps);
	if (ret >= 0)
		return ret;

	/* Fallback to PIO mode */
	return sunxi_nfc_hw_ecc_read_page(nand, buf, oob_required, page);
}