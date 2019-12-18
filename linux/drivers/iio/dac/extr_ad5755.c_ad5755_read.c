#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct spi_transfer {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5755_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {void* d32; int /*<<< orphan*/ * d8; } ;

/* Variables and functions */
 unsigned int AD5755_NOOP ; 
 unsigned int AD5755_READ_FLAG ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (unsigned int) ; 
 struct ad5755_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5755_read(struct iio_dev *indio_dev, unsigned int addr)
{
	struct ad5755_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		},
	};

	mutex_lock(&indio_dev->mlock);

	st->data[0].d32 = cpu_to_be32(AD5755_READ_FLAG | (addr << 16));
	st->data[1].d32 = cpu_to_be32(AD5755_NOOP);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret >= 0)
		ret = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&indio_dev->mlock);

	return ret;
}