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
struct iio_dev {TYPE_1__* setup_ops; } ;
struct TYPE_2__ {int (* validate_scan_mask ) (struct iio_dev*,unsigned long const*) ;} ;

/* Variables and functions */
 int stub1 (struct iio_dev*,unsigned long const*) ; 

__attribute__((used)) static bool iio_validate_scan_mask(struct iio_dev *indio_dev,
	const unsigned long *mask)
{
	if (!indio_dev->setup_ops->validate_scan_mask)
		return true;

	return indio_dev->setup_ops->validate_scan_mask(indio_dev, mask);
}