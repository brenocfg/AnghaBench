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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct ad8366_state {unsigned char* data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (unsigned char*) ; 
 unsigned char bitrev8 (unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ad8366_state* iio_priv (struct iio_dev*) ; 
 int spi_write (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad8366_write(struct iio_dev *indio_dev,
			unsigned char ch_a, unsigned char ch_b)
{
	struct ad8366_state *st = iio_priv(indio_dev);
	int ret;

	ch_a = bitrev8(ch_a & 0x3F);
	ch_b = bitrev8(ch_b & 0x3F);

	st->data[0] = ch_b >> 4;
	st->data[1] = (ch_b << 4) | (ch_a >> 2);

	ret = spi_write(st->spi, st->data, ARRAY_SIZE(st->data));
	if (ret < 0)
		dev_err(&indio_dev->dev, "write failed (%d)", ret);

	return ret;
}