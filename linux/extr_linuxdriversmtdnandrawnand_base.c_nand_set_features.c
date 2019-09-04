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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int (* set_features ) (struct mtd_info*,struct nand_chip*,int,int /*<<< orphan*/ *) ;} ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  nand_supports_set_features (struct nand_chip*,int) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int stub1 (struct mtd_info*,struct nand_chip*,int,int /*<<< orphan*/ *) ; 

int nand_set_features(struct nand_chip *chip, int addr,
		      u8 *subfeature_param)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (!nand_supports_set_features(chip, addr))
		return -ENOTSUPP;

	return chip->set_features(mtd, chip, addr, subfeature_param);
}