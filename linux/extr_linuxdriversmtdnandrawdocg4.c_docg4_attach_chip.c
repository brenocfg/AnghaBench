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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;
struct docg4_priv {int /*<<< orphan*/  bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOCG4_M ; 
 int /*<<< orphan*/  DOCG4_PRIMITIVE_POLY ; 
 int /*<<< orphan*/  DOCG4_T ; 
 int EINVAL ; 
 int /*<<< orphan*/  free_bch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_bch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_mtd_structs (struct mtd_info*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int read_id_reg (struct mtd_info*) ; 
 int /*<<< orphan*/  reset (struct mtd_info*) ; 

__attribute__((used)) static int docg4_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct docg4_priv *doc = (struct docg4_priv *)(chip + 1);
	int ret;

	init_mtd_structs(mtd);

	/* Initialize kernel BCH algorithm */
	doc->bch = init_bch(DOCG4_M, DOCG4_T, DOCG4_PRIMITIVE_POLY);
	if (!doc->bch)
		return -EINVAL;

	reset(mtd);

	ret = read_id_reg(mtd);
	if (ret)
		free_bch(doc->bch);

	return ret;
}