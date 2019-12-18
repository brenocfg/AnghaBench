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
struct mtd_info {struct fsl_upm_nand* name; } ;
struct fsl_upm_nand {int mchip_count; scalar_t__* rnb_gpio; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 struct fsl_upm_nand* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct fsl_upm_nand*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ *) ; 
 struct mtd_info* nand_to_mtd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fun_remove(struct platform_device *ofdev)
{
	struct fsl_upm_nand *fun = dev_get_drvdata(&ofdev->dev);
	struct mtd_info *mtd = nand_to_mtd(&fun->chip);
	int i;

	nand_release(&fun->chip);
	kfree(mtd->name);

	for (i = 0; i < fun->mchip_count; i++) {
		if (fun->rnb_gpio[i] < 0)
			break;
		gpio_free(fun->rnb_gpio[i]);
	}

	kfree(fun);

	return 0;
}