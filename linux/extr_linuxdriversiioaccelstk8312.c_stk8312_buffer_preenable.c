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
struct stk8312_data {int mode; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int STK8312_MODE_ACTIVE ; 
 struct stk8312_data* iio_priv (struct iio_dev*) ; 
 int stk8312_set_mode (struct stk8312_data*,int) ; 

__attribute__((used)) static int stk8312_buffer_preenable(struct iio_dev *indio_dev)
{
	struct stk8312_data *data = iio_priv(indio_dev);

	return stk8312_set_mode(data, data->mode | STK8312_MODE_ACTIVE);
}