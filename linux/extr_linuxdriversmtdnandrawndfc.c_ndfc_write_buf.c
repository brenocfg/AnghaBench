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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ndfc_controller {scalar_t__ ndfcbase; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDFC_DATA ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct ndfc_controller* nand_get_controller_data (struct nand_chip*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ndfc_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct ndfc_controller *ndfc = nand_get_controller_data(chip);
	uint32_t *p = (uint32_t *) buf;

	for(;len > 0; len -= 4)
		out_be32(ndfc->ndfcbase + NDFC_DATA, *p++);
}