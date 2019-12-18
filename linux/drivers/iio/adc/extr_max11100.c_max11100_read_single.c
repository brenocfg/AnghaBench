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
struct max11100_state {int* buffer; int /*<<< orphan*/  spi; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct max11100_state* iio_priv (struct iio_dev*) ; 
 int spi_read (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int max11100_read_single(struct iio_dev *indio_dev, int *val)
{
	int ret;
	struct max11100_state *state = iio_priv(indio_dev);

	ret = spi_read(state->spi, state->buffer, sizeof(state->buffer));
	if (ret) {
		dev_err(&indio_dev->dev, "SPI transfer failed\n");
		return ret;
	}

	/* the first 8 bits sent out from ADC must be 0s */
	if (state->buffer[0]) {
		dev_err(&indio_dev->dev, "Invalid value: buffer[0] != 0\n");
		return -EINVAL;
	}

	*val = (state->buffer[1] << 8) | state->buffer[2];

	return 0;
}