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
typedef  int u16 ;
struct spi_transfer {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct iio_dev {int dummy; } ;
struct adis16080_state {int /*<<< orphan*/  buf; int /*<<< orphan*/  us; } ;

/* Variables and functions */
 int ADIS16080_DIN_WRITE ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 struct adis16080_state* iio_priv (struct iio_dev*) ; 
 int sign_extend32 (int /*<<< orphan*/ ,int) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adis16080_read_sample(struct iio_dev *indio_dev,
		u16 addr, int *val)
{
	struct adis16080_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer	t[] = {
		{
			.tx_buf		= &st->buf,
			.len		= 2,
			.cs_change	= 1,
		}, {
			.rx_buf		= &st->buf,
			.len		= 2,
		},
	};

	st->buf = cpu_to_be16(addr | ADIS16080_DIN_WRITE);

	ret = spi_sync_transfer(st->us, t, ARRAY_SIZE(t));
	if (ret == 0)
		*val = sign_extend32(be16_to_cpu(st->buf), 11);

	return ret;
}