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
struct max30100_data {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 struct max30100_data* iio_priv (struct iio_dev*) ; 
 int max30100_set_powermode (struct max30100_data*,int) ; 

__attribute__((used)) static int max30100_buffer_predisable(struct iio_dev *indio_dev)
{
	struct max30100_data *data = iio_priv(indio_dev);

	return max30100_set_powermode(data, false);
}