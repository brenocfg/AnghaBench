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
struct adxl372_state {unsigned int watermark; } ;

/* Variables and functions */
 unsigned int ADXL372_FIFO_SIZE ; 
 struct adxl372_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int adxl372_set_watermark(struct iio_dev *indio_dev, unsigned int val)
{
	struct adxl372_state *st  = iio_priv(indio_dev);

	if (val > ADXL372_FIFO_SIZE)
		val = ADXL372_FIFO_SIZE;

	st->watermark = val;

	return 0;
}