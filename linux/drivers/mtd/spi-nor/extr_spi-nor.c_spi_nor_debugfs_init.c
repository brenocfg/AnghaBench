#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  partid; int /*<<< orphan*/  partname; } ;
struct mtd_info {TYPE_1__ dbg; } ;
struct spi_nor {int /*<<< orphan*/  dev; struct mtd_info mtd; } ;
struct flash_info {int /*<<< orphan*/  id; int /*<<< orphan*/  id_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spi_nor_debugfs_init(struct spi_nor *nor,
				 const struct flash_info *info)
{
	struct mtd_info *mtd = &nor->mtd;

	mtd->dbg.partname = info->name;
	mtd->dbg.partid = devm_kasprintf(nor->dev, GFP_KERNEL, "spi-nor:%*phN",
					 info->id_len, info->id);
}