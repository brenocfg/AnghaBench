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
struct bmg160_data {int dummy; } ;

/* Variables and functions */
 int bmg160_set_power_state (struct bmg160_data*,int) ; 
 struct bmg160_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int bmg160_buffer_preenable(struct iio_dev *indio_dev)
{
	struct bmg160_data *data = iio_priv(indio_dev);

	return bmg160_set_power_state(data, true);
}