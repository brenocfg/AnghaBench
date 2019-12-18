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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ndfc_controller {int /*<<< orphan*/  chip; } ;
struct mtd_info {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct ndfc_controller* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ndfc_remove(struct platform_device *ofdev)
{
	struct ndfc_controller *ndfc = dev_get_drvdata(&ofdev->dev);
	struct mtd_info *mtd = nand_to_mtd(&ndfc->chip);

	nand_release(&ndfc->chip);
	kfree(mtd->name);

	return 0;
}