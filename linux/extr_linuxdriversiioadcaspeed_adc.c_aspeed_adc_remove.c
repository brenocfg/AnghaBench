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
struct iio_dev {int dummy; } ;
struct aspeed_adc_data {TYPE_1__* clk_prescaler; TYPE_1__* clk_scaler; int /*<<< orphan*/  rst; scalar_t__ base; } ;
struct TYPE_2__ {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_OPERATION_MODE_POWER_DOWN ; 
 scalar_t__ ASPEED_REG_ENGINE_CONTROL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_divider (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct aspeed_adc_data* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aspeed_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct aspeed_adc_data *data = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);
	writel(ASPEED_OPERATION_MODE_POWER_DOWN,
		data->base + ASPEED_REG_ENGINE_CONTROL);
	clk_disable_unprepare(data->clk_scaler->clk);
	reset_control_assert(data->rst);
	clk_hw_unregister_divider(data->clk_scaler);
	clk_hw_unregister_divider(data->clk_prescaler);

	return 0;
}