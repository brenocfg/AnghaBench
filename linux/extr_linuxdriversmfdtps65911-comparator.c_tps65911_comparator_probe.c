#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tps65910_board {int /*<<< orphan*/  vmbch2_threshold; int /*<<< orphan*/  vmbch_threshold; } ;
struct tps65910 {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP1 ; 
 int /*<<< orphan*/  COMP2 ; 
 int comp_threshold_set (struct tps65910*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_comp1_threshold ; 
 int /*<<< orphan*/  dev_attr_comp2_threshold ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps65910_board* dev_get_platdata (int /*<<< orphan*/ ) ; 
 int device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps65911_comparator_probe(struct platform_device *pdev)
{
	struct tps65910 *tps65910 = dev_get_drvdata(pdev->dev.parent);
	struct tps65910_board *pdata = dev_get_platdata(tps65910->dev);
	int ret;

	ret = comp_threshold_set(tps65910, COMP1,  pdata->vmbch_threshold);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot set COMP1 threshold\n");
		return ret;
	}

	ret = comp_threshold_set(tps65910, COMP2, pdata->vmbch2_threshold);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot set COMP2 threshold\n");
		return ret;
	}

	/* Create sysfs entry */
	ret = device_create_file(&pdev->dev, &dev_attr_comp1_threshold);
	if (ret < 0)
		dev_err(&pdev->dev, "failed to add COMP1 sysfs file\n");

	ret = device_create_file(&pdev->dev, &dev_attr_comp2_threshold);
	if (ret < 0)
		dev_err(&pdev->dev, "failed to add COMP2 sysfs file\n");

	return ret;
}