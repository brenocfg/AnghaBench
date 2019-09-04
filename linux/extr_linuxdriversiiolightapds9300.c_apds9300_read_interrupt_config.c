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
struct iio_chan_spec {int dummy; } ;
struct apds9300_data {int intr_en; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 struct apds9300_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int apds9300_read_interrupt_config(struct iio_dev *indio_dev,
		const struct iio_chan_spec *chan,
		enum iio_event_type type,
		enum iio_event_direction dir)
{
	struct apds9300_data *data = iio_priv(indio_dev);

	return data->intr_en;
}