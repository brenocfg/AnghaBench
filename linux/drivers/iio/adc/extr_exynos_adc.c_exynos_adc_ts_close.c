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
struct input_dev {int dummy; } ;
struct exynos_adc {int /*<<< orphan*/  tsirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct exynos_adc* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void exynos_adc_ts_close(struct input_dev *dev)
{
	struct exynos_adc *info = input_get_drvdata(dev);

	disable_irq(info->tsirq);
}