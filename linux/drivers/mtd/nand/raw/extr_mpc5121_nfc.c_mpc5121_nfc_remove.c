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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 struct mtd_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mpc5121_nfc_free (struct device*,struct mtd_info*) ; 
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 int /*<<< orphan*/  nand_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mpc5121_nfc_remove(struct platform_device *op)
{
	struct device *dev = &op->dev;
	struct mtd_info *mtd = dev_get_drvdata(dev);

	nand_release(mtd_to_nand(mtd));
	mpc5121_nfc_free(dev, mtd);

	return 0;
}