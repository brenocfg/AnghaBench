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
struct bch_geometry {int ecc_strength; unsigned int gf_len; unsigned int ecc_chunk_size; int /*<<< orphan*/  page_size; int /*<<< orphan*/  metadata_size; scalar_t__ ecc_chunk_count; } ;
struct gpmi_nand_data {int bch_flashlayout0; int bch_flashlayout1; struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 int BF_BCH_FLASH0LAYOUT0_DATA0_SIZE (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_ECC0 (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_GF (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT0_META_SIZE (int /*<<< orphan*/ ) ; 
 int BF_BCH_FLASH0LAYOUT0_NBLOCKS (scalar_t__) ; 
 int BF_BCH_FLASH0LAYOUT1_DATAN_SIZE (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_ECCN (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_GF (unsigned int,struct gpmi_nand_data*) ; 
 int BF_BCH_FLASH0LAYOUT1_PAGE_SIZE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gpmi_bch_layout_std(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;
	unsigned int ecc_strength = geo->ecc_strength >> 1;
	unsigned int gf_len = geo->gf_len;
	unsigned int block_size = geo->ecc_chunk_size;

	this->bch_flashlayout0 =
		BF_BCH_FLASH0LAYOUT0_NBLOCKS(geo->ecc_chunk_count - 1) |
		BF_BCH_FLASH0LAYOUT0_META_SIZE(geo->metadata_size) |
		BF_BCH_FLASH0LAYOUT0_ECC0(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT0_GF(gf_len, this) |
		BF_BCH_FLASH0LAYOUT0_DATA0_SIZE(block_size, this);

	this->bch_flashlayout1 =
		BF_BCH_FLASH0LAYOUT1_PAGE_SIZE(geo->page_size) |
		BF_BCH_FLASH0LAYOUT1_ECCN(ecc_strength, this) |
		BF_BCH_FLASH0LAYOUT1_GF(gf_len, this) |
		BF_BCH_FLASH0LAYOUT1_DATAN_SIZE(block_size, this);
}