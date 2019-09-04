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
struct platform_device {int dummy; } ;
struct nand_chip {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct mtd_info {TYPE_1__ dev; } ;
struct jz_nand_platform_data {int /*<<< orphan*/  num_partitions; int /*<<< orphan*/  partitions; int /*<<< orphan*/  (* ident_callback ) (struct platform_device*,struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 struct jz_nand_platform_data* dev_get_platdata (struct device*) ; 
 struct mtd_info* nand_to_mtd (struct nand_chip*) ; 
 int /*<<< orphan*/  stub1 (struct platform_device*,struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int jz_nand_attach_chip(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	struct device *dev = mtd->dev.parent;
	struct jz_nand_platform_data *pdata = dev_get_platdata(dev);
	struct platform_device *pdev = to_platform_device(dev);

	if (pdata && pdata->ident_callback)
		pdata->ident_callback(pdev, mtd, &pdata->partitions,
				      &pdata->num_partitions);

	return 0;
}