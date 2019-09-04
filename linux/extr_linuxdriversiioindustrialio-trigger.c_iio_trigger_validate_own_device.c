#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ parent; } ;
struct iio_trigger {TYPE_2__ dev; } ;
struct TYPE_3__ {scalar_t__ parent; } ;
struct iio_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 

int iio_trigger_validate_own_device(struct iio_trigger *trig,
	struct iio_dev *indio_dev)
{
	if (indio_dev->dev.parent != trig->dev.parent)
		return -EINVAL;
	return 0;
}