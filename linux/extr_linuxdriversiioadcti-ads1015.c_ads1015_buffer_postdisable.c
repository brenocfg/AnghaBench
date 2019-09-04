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
 int ads1015_set_power_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ads1015_buffer_postdisable(struct iio_dev *indio_dev)
{
	return ads1015_set_power_state(iio_priv(indio_dev), false);
}