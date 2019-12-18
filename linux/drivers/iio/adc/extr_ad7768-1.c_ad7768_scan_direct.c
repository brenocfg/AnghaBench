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
struct ad7768_state {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7768_CONTINUOUS ; 
 int /*<<< orphan*/  AD7768_ONE_SHOT ; 
 int /*<<< orphan*/  AD7768_REG_ADC_DATA ; 
 int ETIMEDOUT ; 
 int ad7768_set_mode (struct ad7768_state*,int /*<<< orphan*/ ) ; 
 int ad7768_spi_reg_read (struct ad7768_state*,int /*<<< orphan*/ ,int) ; 
 struct ad7768_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad7768_scan_direct(struct iio_dev *indio_dev)
{
	struct ad7768_state *st = iio_priv(indio_dev);
	int readval, ret;

	reinit_completion(&st->completion);

	ret = ad7768_set_mode(st, AD7768_ONE_SHOT);
	if (ret < 0)
		return ret;

	ret = wait_for_completion_timeout(&st->completion,
					  msecs_to_jiffies(1000));
	if (!ret)
		return -ETIMEDOUT;

	readval = ad7768_spi_reg_read(st, AD7768_REG_ADC_DATA, 3);
	if (readval < 0)
		return readval;
	/*
	 * Any SPI configuration of the AD7768-1 can only be
	 * performed in continuous conversion mode.
	 */
	ret = ad7768_set_mode(st, AD7768_CONTINUOUS);
	if (ret < 0)
		return ret;

	return readval;
}