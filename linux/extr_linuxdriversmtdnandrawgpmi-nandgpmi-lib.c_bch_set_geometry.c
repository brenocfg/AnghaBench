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
struct resources {scalar_t__ bch_regs; } ;
struct bch_geometry {int ecc_chunk_count; unsigned int ecc_chunk_size; unsigned int metadata_size; int ecc_strength; unsigned int page_size; unsigned int gf_len; } ;
struct gpmi_nand_data {struct bch_geometry bch_geometry; struct resources resources; } ;

/* Variables and functions */
 int BF_BCH_FLASH0LAYOUT0_DATA0_SIZE (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_ECC0 (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_GF (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_META_SIZE (unsigned int) ; 
 int BF_BCH_FLASH0LAYOUT0_NBLOCKS (unsigned int) ; 
 int BF_BCH_FLASH0LAYOUT1_DATAN_SIZE (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_ECCN (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_GF (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_PAGE_SIZE (unsigned int) ; 
 int BM_BCH_CTRL_COMPLETE_IRQ_EN ; 
 scalar_t__ GPMI_IS_MX23 (struct gpmi_nand_data*) ; 
 scalar_t__ GPMI_IS_MX28 (struct gpmi_nand_data*) ; 
 scalar_t__ HW_BCH_CTRL_SET ; 
 scalar_t__ HW_BCH_FLASH0LAYOUT0 ; 
 scalar_t__ HW_BCH_FLASH0LAYOUT1 ; 
 scalar_t__ HW_BCH_LAYOUTSELECT ; 
 int common_nfc_set_geometry (struct gpmi_nand_data*) ; 
 int /*<<< orphan*/  gpmi_disable_clk (struct gpmi_nand_data*) ; 
 int gpmi_enable_clk (struct gpmi_nand_data*) ; 
 int gpmi_reset_block (scalar_t__,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int bch_set_geometry(struct gpmi_nand_data *this)
{
	struct resources *r = &this->resources;
	struct bch_geometry *bch_geo = &this->bch_geometry;
	unsigned int block_count;
	unsigned int block_size;
	unsigned int metadata_size;
	unsigned int ecc_strength;
	unsigned int page_size;
	unsigned int gf_len;
	int ret;

	ret = common_nfc_set_geometry(this);
	if (ret)
		return ret;

	block_count   = bch_geo->ecc_chunk_count - 1;
	block_size    = bch_geo->ecc_chunk_size;
	metadata_size = bch_geo->metadata_size;
	ecc_strength  = bch_geo->ecc_strength >> 1;
	page_size     = bch_geo->page_size;
	gf_len        = bch_geo->gf_len;

	ret = gpmi_enable_clk(this);
	if (ret)
		return ret;

	/*
	* Due to erratum #2847 of the MX23, the BCH cannot be soft reset on this
	* chip, otherwise it will lock up. So we skip resetting BCH on the MX23.
	* and MX28.
	*/
	ret = gpmi_reset_block(r->bch_regs,
			       GPMI_IS_MX23(this) || GPMI_IS_MX28(this));
	if (ret)
		goto err_out;

	/* Configure layout 0. */
	writel(BF_BCH_FLASH0LAYOUT0_NBLOCKS(block_count)
			| BF_BCH_FLASH0LAYOUT0_META_SIZE(metadata_size)
			| BF_BCH_FLASH0LAYOUT0_ECC0(ecc_strength, this)
			| BF_BCH_FLASH0LAYOUT0_GF(gf_len, this)
			| BF_BCH_FLASH0LAYOUT0_DATA0_SIZE(block_size, this),
			r->bch_regs + HW_BCH_FLASH0LAYOUT0);

	writel(BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(page_size)
			| BF_BCH_FLASH0LAYOUT1_ECCN(ecc_strength, this)
			| BF_BCH_FLASH0LAYOUT1_GF(gf_len, this)
			| BF_BCH_FLASH0LAYOUT1_DATAN_SIZE(block_size, this),
			r->bch_regs + HW_BCH_FLASH0LAYOUT1);

	/* Set *all* chip selects to use layout 0. */
	writel(0, r->bch_regs + HW_BCH_LAYOUTSELECT);

	/* Enable interrupts. */
	writel(BM_BCH_CTRL_COMPLETE_IRQ_EN,
				r->bch_regs + HW_BCH_CTRL_SET);

	gpmi_disable_clk(this);
	return 0;
err_out:
	gpmi_disable_clk(this);
	return ret;
}