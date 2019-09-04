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
struct mtd_info {int dummy; } ;
struct jz_nand {int /*<<< orphan*/  busy_gpio; } ;

/* Variables and functions */
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 struct jz_nand* mtd_to_jz_nand (struct mtd_info*) ; 

__attribute__((used)) static int jz_nand_dev_ready(struct mtd_info *mtd)
{
	struct jz_nand *nand = mtd_to_jz_nand(mtd);
	return gpiod_get_value_cansleep(nand->busy_gpio);
}