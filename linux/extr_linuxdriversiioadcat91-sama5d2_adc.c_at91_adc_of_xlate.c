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
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int at91_adc_chan_xlate (struct iio_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int at91_adc_of_xlate(struct iio_dev *indio_dev,
				    const struct of_phandle_args *iiospec)
{
	return at91_adc_chan_xlate(indio_dev, iiospec->args[0]);
}