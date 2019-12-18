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
struct s3c2410_nand_set {int /*<<< orphan*/  nr_partitions; int /*<<< orphan*/  partitions; int /*<<< orphan*/  name; } ;
struct s3c2410_nand_mtd {int /*<<< orphan*/  chip; } ;
struct s3c2410_nand_info {int dummy; } ;
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int mtd_device_register (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c2410_nand_add_partition(struct s3c2410_nand_info *info,
				      struct s3c2410_nand_mtd *mtd,
				      struct s3c2410_nand_set *set)
{
	if (set) {
		struct mtd_info *mtdinfo = nand_to_mtd(&mtd->chip);

		mtdinfo->name = set->name;

		return mtd_device_register(mtdinfo, set->partitions,
					   set->nr_partitions);
	}

	return -ENODEV;
}