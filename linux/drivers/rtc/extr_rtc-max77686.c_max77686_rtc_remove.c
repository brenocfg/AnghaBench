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
struct max77686_rtc_info {int /*<<< orphan*/  rtc_irq_data; int /*<<< orphan*/  rtc_irq; int /*<<< orphan*/  virq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct max77686_rtc_info*) ; 
 struct max77686_rtc_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77686_rtc_remove(struct platform_device *pdev)
{
	struct max77686_rtc_info *info = platform_get_drvdata(pdev);

	free_irq(info->virq, info);
	regmap_del_irq_chip(info->rtc_irq, info->rtc_irq_data);

	return 0;
}