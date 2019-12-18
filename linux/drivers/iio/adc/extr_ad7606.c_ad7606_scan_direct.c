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
struct ad7606_state {int* data; int /*<<< orphan*/  gpio_convst; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int ad7606_read_samples (struct ad7606_state*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct ad7606_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7606_scan_direct(struct iio_dev *indio_dev, unsigned int ch)
{
	struct ad7606_state *st = iio_priv(indio_dev);
	int ret;

	gpiod_set_value(st->gpio_convst, 1);
	ret = wait_for_completion_timeout(&st->completion,
					  msecs_to_jiffies(1000));
	if (!ret) {
		ret = -ETIMEDOUT;
		goto error_ret;
	}

	ret = ad7606_read_samples(st);
	if (ret == 0)
		ret = st->data[ch];

error_ret:
	gpiod_set_value(st->gpio_convst, 0);

	return ret;
}