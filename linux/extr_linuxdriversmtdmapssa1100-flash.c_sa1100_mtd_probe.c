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
struct sa_info {int /*<<< orphan*/  mtd; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct flash_platform_data {int /*<<< orphan*/  nr_parts; int /*<<< orphan*/  parts; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct sa_info*) ; 
 int PTR_ERR (struct sa_info*) ; 
 struct flash_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_device_parse_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_probes ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sa_info*) ; 
 struct sa_info* sa1100_setup_mtd (struct platform_device*,struct flash_platform_data*) ; 

__attribute__((used)) static int sa1100_mtd_probe(struct platform_device *pdev)
{
	struct flash_platform_data *plat = dev_get_platdata(&pdev->dev);
	struct sa_info *info;
	int err;

	if (!plat)
		return -ENODEV;

	info = sa1100_setup_mtd(pdev, plat);
	if (IS_ERR(info)) {
		err = PTR_ERR(info);
		goto out;
	}

	/*
	 * Partition selection stuff.
	 */
	mtd_device_parse_register(info->mtd, part_probes, NULL, plat->parts,
				  plat->nr_parts);

	platform_set_drvdata(pdev, info);
	err = 0;

 out:
	return err;
}