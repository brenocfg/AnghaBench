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
struct TYPE_2__ {int als_interrupt_en; int prox_interrupt_en; } ;
struct tsl2772_chip {TYPE_1__ settings; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {scalar_t__ type; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 scalar_t__ IIO_INTENSITY ; 
 struct tsl2772_chip* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int tsl2772_read_interrupt_config(struct iio_dev *indio_dev,
					 const struct iio_chan_spec *chan,
					 enum iio_event_type type,
					 enum iio_event_direction dir)
{
	struct tsl2772_chip *chip = iio_priv(indio_dev);

	if (chan->type == IIO_INTENSITY)
		return chip->settings.als_interrupt_en;
	else
		return chip->settings.prox_interrupt_en;
}