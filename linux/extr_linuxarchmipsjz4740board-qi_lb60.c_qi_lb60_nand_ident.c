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
struct platform_device {int dummy; } ;
struct nand_chip {int page_shift; } ;
struct mtd_partition {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mtd_partition*) ; 
 int /*<<< orphan*/  mtd_set_ooblayout (struct mtd_info*,int /*<<< orphan*/ *) ; 
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  qi_lb60_ooblayout_ops ; 
 struct mtd_partition* qi_lb60_partitions_1gb ; 
 struct mtd_partition* qi_lb60_partitions_2gb ; 

__attribute__((used)) static void qi_lb60_nand_ident(struct platform_device *pdev,
		struct mtd_info *mtd, struct mtd_partition **partitions,
		int *num_partitions)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (chip->page_shift == 12) {
		*partitions = qi_lb60_partitions_2gb;
		*num_partitions = ARRAY_SIZE(qi_lb60_partitions_2gb);
	} else {
		*partitions = qi_lb60_partitions_1gb;
		*num_partitions = ARRAY_SIZE(qi_lb60_partitions_1gb);
	}

	mtd_set_ooblayout(mtd, &qi_lb60_ooblayout_ops);
}