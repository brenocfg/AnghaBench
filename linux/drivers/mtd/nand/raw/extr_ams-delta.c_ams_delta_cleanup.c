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
struct mtd_info {int dummy; } ;
struct ams_delta_nand {int /*<<< orphan*/  nand_chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 
 struct ams_delta_nand* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ams_delta_cleanup(struct platform_device *pdev)
{
	struct ams_delta_nand *priv = platform_get_drvdata(pdev);
	struct mtd_info *mtd = nand_to_mtd(&priv->nand_chip);

	/* Unregister device */
	nand_release(mtd_to_nand(mtd));

	return 0;
}