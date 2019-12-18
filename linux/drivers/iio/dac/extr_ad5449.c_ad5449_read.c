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
struct spi_transfer {int len; int cs_change; void** rx_buf; void** tx_buf; } ;
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct ad5449 {void** data; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 unsigned int AD5449_CMD_NOOP ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 unsigned int be16_to_cpu (void*) ; 
 void* cpu_to_be16 (unsigned int) ; 
 struct ad5449* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5449_read(struct iio_dev *indio_dev, unsigned int addr,
	unsigned int *val)
{
	struct ad5449 *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0],
			.len = 2,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1],
			.rx_buf = &st->data[1],
			.len = 2,
		},
	};

	mutex_lock(&indio_dev->mlock);
	st->data[0] = cpu_to_be16(addr << 12);
	st->data[1] = cpu_to_be16(AD5449_CMD_NOOP);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret < 0)
		goto out_unlock;

	*val = be16_to_cpu(st->data[1]);

out_unlock:
	mutex_unlock(&indio_dev->mlock);
	return ret;
}