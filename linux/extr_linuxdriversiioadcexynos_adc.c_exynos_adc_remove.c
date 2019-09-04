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
struct platform_device {int dummy; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct exynos_adc {int /*<<< orphan*/  vdd; TYPE_1__* data; int /*<<< orphan*/  irq; scalar_t__ input; int /*<<< orphan*/  tsirq; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* exit_hw ) (struct exynos_adc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INPUT ; 
 scalar_t__ IS_REACHABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_adc_disable_clk (struct exynos_adc*) ; 
 int /*<<< orphan*/  exynos_adc_remove_devices ; 
 int /*<<< orphan*/  exynos_adc_unprepare_clk (struct exynos_adc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct exynos_adc*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct exynos_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct exynos_adc*) ; 

__attribute__((used)) static int exynos_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct exynos_adc *info = iio_priv(indio_dev);

	if (IS_REACHABLE(CONFIG_INPUT) && info->input) {
		free_irq(info->tsirq, info);
		input_unregister_device(info->input);
	}
	device_for_each_child(&indio_dev->dev, NULL,
				exynos_adc_remove_devices);
	iio_device_unregister(indio_dev);
	free_irq(info->irq, info);
	if (info->data->exit_hw)
		info->data->exit_hw(info);
	exynos_adc_disable_clk(info);
	exynos_adc_unprepare_clk(info);
	regulator_disable(info->vdd);

	return 0;
}