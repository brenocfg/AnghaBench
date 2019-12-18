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
struct at91_adc_state {int /*<<< orphan*/  reg; int /*<<< orphan*/  vref; int /*<<< orphan*/  per_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91_adc_dma_disable (struct platform_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct at91_adc_state* iio_priv (struct iio_dev*) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at91_adc_remove(struct platform_device *pdev)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct at91_adc_state *st = iio_priv(indio_dev);

	iio_device_unregister(indio_dev);

	at91_adc_dma_disable(pdev);

	clk_disable_unprepare(st->per_clk);

	regulator_disable(st->vref);
	regulator_disable(st->reg);

	return 0;
}