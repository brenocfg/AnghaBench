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
struct mxs_lradc_adc {int /*<<< orphan*/  trig; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct mxs_lradc_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxs_lradc_adc_trigger_remove(struct iio_dev *iio)
{
	struct mxs_lradc_adc *adc = iio_priv(iio);

	iio_trigger_unregister(adc->trig);
}