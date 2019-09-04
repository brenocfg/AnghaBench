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
struct tps65910 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_comp1_threshold ; 
 int /*<<< orphan*/  dev_attr_comp2_threshold ; 
 struct tps65910* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tps65911_comparator_remove(struct platform_device *pdev)
{
	struct tps65910 *tps65910;

	tps65910 = dev_get_drvdata(pdev->dev.parent);
	device_remove_file(&pdev->dev, &dev_attr_comp2_threshold);
	device_remove_file(&pdev->dev, &dev_attr_comp1_threshold);

	return 0;
}