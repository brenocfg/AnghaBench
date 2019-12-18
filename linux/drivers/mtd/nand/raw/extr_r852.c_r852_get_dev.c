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
struct r852_device {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct nand_chip* mtd_to_nand (struct mtd_info*) ; 
 struct r852_device* nand_get_controller_data (struct nand_chip*) ; 

__attribute__((used)) static inline struct r852_device *r852_get_dev(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	return nand_get_controller_data(chip);
}