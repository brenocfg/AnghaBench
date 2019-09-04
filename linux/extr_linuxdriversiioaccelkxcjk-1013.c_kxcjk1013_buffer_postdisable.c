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
struct kxcjk1013_data {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct kxcjk1013_data* iio_priv (struct iio_dev*) ; 
 int kxcjk1013_set_power_state (struct kxcjk1013_data*,int) ; 

__attribute__((used)) static int kxcjk1013_buffer_postdisable(struct iio_dev *indio_dev)
{
	struct kxcjk1013_data *data = iio_priv(indio_dev);

	return kxcjk1013_set_power_state(data, false);
}