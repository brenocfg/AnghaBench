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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  scan_index; } ;
struct ad799x_state {int config; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int AD7998_ALERT_EN ; 
 int AD799X_CHANNEL_SHIFT ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int ad799x_write_config (struct ad799x_state*,int) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ad799x_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad799x_write_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     int state)
{
	struct ad799x_state *st = iio_priv(indio_dev);
	int ret;

	ret = iio_device_claim_direct_mode(indio_dev);
	if (ret)
		return ret;

	if (state)
		st->config |= BIT(chan->scan_index) << AD799X_CHANNEL_SHIFT;
	else
		st->config &= ~(BIT(chan->scan_index) << AD799X_CHANNEL_SHIFT);

	if (st->config >> AD799X_CHANNEL_SHIFT)
		st->config |= AD7998_ALERT_EN;
	else
		st->config &= ~AD7998_ALERT_EN;

	ret = ad799x_write_config(st, st->config);
	iio_device_release_direct_mode(indio_dev);
	return ret;
}