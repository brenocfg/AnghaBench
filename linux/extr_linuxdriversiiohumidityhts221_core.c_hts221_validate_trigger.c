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
struct iio_trigger {int dummy; } ;
struct iio_dev {int dummy; } ;
struct hts221_hw {struct iio_trigger* trig; } ;

/* Variables and functions */
 int EINVAL ; 
 struct hts221_hw* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int hts221_validate_trigger(struct iio_dev *iio_dev,
				   struct iio_trigger *trig)
{
	struct hts221_hw *hw = iio_priv(iio_dev);

	return hw->trig == trig ? 0 : -EINVAL;
}