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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct nand_chip {int /*<<< orphan*/  cur_cs; TYPE_1__ ecc; } ;

/* Variables and functions */
 int DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_read_page_op (struct nand_chip*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sunxi_nfc_hw_ecc_read_chunks_dma (struct nand_chip*,int /*<<< orphan*/ *,int,int,int) ; 
 int sunxi_nfc_hw_ecc_read_subpage (struct nand_chip*,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sunxi_nfc_select_chip (struct nand_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sunxi_nfc_hw_ecc_read_subpage_dma(struct nand_chip *nand,
					     u32 data_offs, u32 readlen,
					     u8 *buf, int page)
{
	int nchunks = DIV_ROUND_UP(data_offs + readlen, nand->ecc.size);
	int ret;

	sunxi_nfc_select_chip(nand, nand->cur_cs);

	nand_read_page_op(nand, page, 0, NULL, 0);

	ret = sunxi_nfc_hw_ecc_read_chunks_dma(nand, buf, false, page, nchunks);
	if (ret >= 0)
		return ret;

	/* Fallback to PIO mode */
	return sunxi_nfc_hw_ecc_read_subpage(nand, data_offs, readlen,
					     buf, page);
}