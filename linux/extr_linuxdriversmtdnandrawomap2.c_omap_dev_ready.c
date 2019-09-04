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
struct omap_nand_info {int /*<<< orphan*/  ready_gpiod; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int gpiod_get_value (int /*<<< orphan*/ ) ; 
 struct omap_nand_info* mtd_to_omap (struct mtd_info*) ; 

__attribute__((used)) static int omap_dev_ready(struct mtd_info *mtd)
{
	struct omap_nand_info *info = mtd_to_omap(mtd);

	return gpiod_get_value(info->ready_gpiod);
}