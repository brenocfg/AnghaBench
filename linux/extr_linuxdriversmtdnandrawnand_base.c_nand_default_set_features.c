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
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int nand_set_features_op (struct nand_chip*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_default_set_features(struct mtd_info *mtd,
				     struct nand_chip *chip, int addr,
				     uint8_t *subfeature_param)
{
	return nand_set_features_op(chip, addr, subfeature_param);
}