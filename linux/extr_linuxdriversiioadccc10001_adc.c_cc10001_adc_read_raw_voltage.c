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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  channel; } ;
struct cc10001_adc_device {unsigned int eoc_delay_ns; int /*<<< orphan*/  shared; } ;

/* Variables and functions */
 unsigned int CC10001_MAX_POLL_COUNT ; 
 int /*<<< orphan*/  cc10001_adc_poll_done (struct iio_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cc10001_adc_power_down (struct cc10001_adc_device*) ; 
 int /*<<< orphan*/  cc10001_adc_power_up (struct cc10001_adc_device*) ; 
 int /*<<< orphan*/  cc10001_adc_start (struct cc10001_adc_device*,int /*<<< orphan*/ ) ; 
 struct cc10001_adc_device* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static u16 cc10001_adc_read_raw_voltage(struct iio_dev *indio_dev,
					struct iio_chan_spec const *chan)
{
	struct cc10001_adc_device *adc_dev = iio_priv(indio_dev);
	unsigned int delay_ns;
	u16 val;

	if (!adc_dev->shared)
		cc10001_adc_power_up(adc_dev);

	/* Calculate delay step for eoc and sampled data */
	delay_ns = adc_dev->eoc_delay_ns / CC10001_MAX_POLL_COUNT;

	cc10001_adc_start(adc_dev, chan->channel);

	val = cc10001_adc_poll_done(indio_dev, chan->channel, delay_ns);

	if (!adc_dev->shared)
		cc10001_adc_power_down(adc_dev);

	return val;
}