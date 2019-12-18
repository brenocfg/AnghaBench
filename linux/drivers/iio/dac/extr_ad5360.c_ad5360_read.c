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
struct ad5360_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  d32; int /*<<< orphan*/ * d8; } ;

/* Variables and functions */
 int AD5360_ADDR (int /*<<< orphan*/ ) ; 
 int AD5360_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD5360_CMD_SPECIAL_FUNCTION ; 
 int AD5360_READBACK_ADDR (unsigned int) ; 
 int AD5360_READBACK_TYPE (unsigned int) ; 
 int /*<<< orphan*/  AD5360_REG_SF_READBACK ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 struct ad5360_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad5360_read(struct iio_dev *indio_dev, unsigned int type,
	unsigned int addr)
{
	struct ad5360_state *st = iio_priv(indio_dev);
	int ret;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		}, {
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		},
	};

	mutex_lock(&indio_dev->mlock);

	st->data[0].d32 = cpu_to_be32(AD5360_CMD(AD5360_CMD_SPECIAL_FUNCTION) |
		AD5360_ADDR(AD5360_REG_SF_READBACK) |
		AD5360_READBACK_TYPE(type) |
		AD5360_READBACK_ADDR(addr));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret >= 0)
		ret = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&indio_dev->mlock);

	return ret;
}