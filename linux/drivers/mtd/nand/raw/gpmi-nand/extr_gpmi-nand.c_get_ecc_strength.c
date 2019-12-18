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
struct mtd_info {int oobsize; } ;
struct bch_geometry {int metadata_size; int gf_len; int ecc_chunk_count; } ;
struct gpmi_nand_data {int /*<<< orphan*/  nand; struct bch_geometry bch_geometry; } ;

/* Variables and functions */
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 
 int round_down (int,int) ; 

__attribute__((used)) static inline int get_ecc_strength(struct gpmi_nand_data *this)
{
	struct bch_geometry *geo = &this->bch_geometry;
	struct mtd_info	*mtd = nand_to_mtd(&this->nand);
	int ecc_strength;

	ecc_strength = ((mtd->oobsize - geo->metadata_size) * 8)
			/ (geo->gf_len * geo->ecc_chunk_count);

	/* We need the minor even number. */
	return round_down(ecc_strength, 2);
}