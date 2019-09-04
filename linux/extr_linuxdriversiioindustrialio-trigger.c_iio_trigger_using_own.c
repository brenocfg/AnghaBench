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
struct iio_dev {TYPE_1__* trig; } ;
struct TYPE_2__ {int attached_own_device; } ;

/* Variables and functions */

bool iio_trigger_using_own(struct iio_dev *indio_dev)
{
	return indio_dev->trig->attached_own_device;
}