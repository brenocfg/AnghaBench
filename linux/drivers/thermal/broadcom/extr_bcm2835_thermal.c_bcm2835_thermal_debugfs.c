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
struct debugfs_regset32 {int /*<<< orphan*/  base; int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; } ;
struct bcm2835_thermal_data {int /*<<< orphan*/  debugfsdir; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_thermal_regs ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_regset32 (char*,int,int /*<<< orphan*/ ,struct debugfs_regset32*) ; 
 struct debugfs_regset32* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct bcm2835_thermal_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void bcm2835_thermal_debugfs(struct platform_device *pdev)
{
	struct bcm2835_thermal_data *data = platform_get_drvdata(pdev);
	struct debugfs_regset32 *regset;

	data->debugfsdir = debugfs_create_dir("bcm2835_thermal", NULL);

	regset = devm_kzalloc(&pdev->dev, sizeof(*regset), GFP_KERNEL);
	if (!regset)
		return;

	regset->regs = bcm2835_thermal_regs;
	regset->nregs = ARRAY_SIZE(bcm2835_thermal_regs);
	regset->base = data->regs;

	debugfs_create_regset32("regset", 0444, data->debugfsdir, regset);
}