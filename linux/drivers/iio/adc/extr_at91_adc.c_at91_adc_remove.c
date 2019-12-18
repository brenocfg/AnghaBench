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
struct iio_dev {int dummy; } ;
struct at91_adc_state {int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  adc_clk; int /*<<< orphan*/  touchscreen_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_buffer_remove (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_adc_trigger_remove (struct iio_dev*) ; 
 int /*<<< orphan*/  at91_ts_unregister (struct at91_adc_state*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int at91_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *idev = platform_get_drvdata(pdev);
	struct at91_adc_state *st = iio_priv(idev);

	iio_device_unregister(idev);
	if (!st->touchscreen_type) {
		at91_adc_trigger_remove(idev);
		at91_adc_buffer_remove(idev);
	} else {
		at91_ts_unregister(st);
	}
	clk_disable_unprepare(st->adc_clk);
	clk_disable_unprepare(st->clk);
	free_irq(st->irq, idev);

	return 0;
}