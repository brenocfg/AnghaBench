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
struct max30102_data {int dummy; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX30102_REG_MODE_CONFIG_MODE_NONE ; 
 struct max30102_data* iio_priv (struct iio_dev*) ; 
 int max30102_set_powermode (struct max30102_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max30102_buffer_predisable(struct iio_dev *indio_dev)
{
	struct max30102_data *data = iio_priv(indio_dev);

	return max30102_set_powermode(data, MAX30102_REG_MODE_CONFIG_MODE_NONE,
				      false);
}