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
typedef  int /*<<< orphan*/  u16 ;
struct platform_device {int dummy; } ;
struct iio_dev {int dummy; } ;
struct dln2_adc {int /*<<< orphan*/  trig; } ;

/* Variables and functions */
 struct dln2_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_trigger_poll (int /*<<< orphan*/ ) ; 
 struct iio_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void dln2_adc_event(struct platform_device *pdev, u16 echo,
			   const void *data, int len)
{
	struct iio_dev *indio_dev = platform_get_drvdata(pdev);
	struct dln2_adc *dln2 = iio_priv(indio_dev);

	/* Called via URB completion handler */
	iio_trigger_poll(dln2->trig);
}