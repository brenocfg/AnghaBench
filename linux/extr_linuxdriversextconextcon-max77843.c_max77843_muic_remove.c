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
struct max77843_muic_info {int /*<<< orphan*/  irq_work; struct max77693_dev* max77843; } ;
struct max77693_dev {int /*<<< orphan*/  i2c_muic; int /*<<< orphan*/  irq_data_muic; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 struct max77843_muic_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77843_muic_remove(struct platform_device *pdev)
{
	struct max77843_muic_info *info = platform_get_drvdata(pdev);
	struct max77693_dev *max77843 = info->max77843;

	cancel_work_sync(&info->irq_work);
	regmap_del_irq_chip(max77843->irq, max77843->irq_data_muic);
	i2c_unregister_device(max77843->i2c_muic);

	return 0;
}