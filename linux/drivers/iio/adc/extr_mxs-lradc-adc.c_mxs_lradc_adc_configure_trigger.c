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
typedef  scalar_t__ u32 ;
struct mxs_lradc_adc {scalar_t__ const base; } ;
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ const LRADC_DELAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LRADC_DELAY_KICK ; 
 scalar_t__ STMP_OFFSET_REG_CLR ; 
 scalar_t__ STMP_OFFSET_REG_SET ; 
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 struct iio_dev* iio_trigger_get_drvdata (struct iio_trigger*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__ const) ; 

__attribute__((used)) static int mxs_lradc_adc_configure_trigger(struct iio_trigger *trig, bool state)
{
	struct iio_dev *iio = iio_trigger_get_drvdata(trig);
	struct mxs_lradc_adc *adc = iio_priv(iio);
	const u32 st = state ? STMP_OFFSET_REG_SET : STMP_OFFSET_REG_CLR;

	writel(LRADC_DELAY_KICK, adc->base + (LRADC_DELAY(0) + st));

	return 0;
}