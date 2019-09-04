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

/* Variables and functions */
 int /*<<< orphan*/  zpa2326_enable_device (struct iio_dev const*) ; 

__attribute__((used)) static int zpa2326_resume(const struct iio_dev *indio_dev)
{
	zpa2326_enable_device(indio_dev);

	return 0;
}