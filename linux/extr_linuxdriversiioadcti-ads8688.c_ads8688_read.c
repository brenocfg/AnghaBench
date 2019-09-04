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
typedef  int /*<<< orphan*/  u32 ;
struct spi_transfer {int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct iio_dev {int dummy; } ;
struct ads8688_state {TYPE_1__* data; int /*<<< orphan*/  spi; } ;
struct TYPE_2__ {void* d32; int /*<<< orphan*/ * d8; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADS8688_CMD_DONT_CARE_BITS ; 
 int /*<<< orphan*/  ADS8688_CMD_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADS8688_CMD_REG_MAN_CH (unsigned int) ; 
 int /*<<< orphan*/  ADS8688_CMD_REG_NOOP ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct ads8688_state* iio_priv (struct iio_dev*) ; 
 int spi_sync_transfer (int /*<<< orphan*/ ,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ads8688_read(struct iio_dev *indio_dev, unsigned int chan)
{
	struct ads8688_state *st = iio_priv(indio_dev);
	int ret;
	u32 tmp;
	struct spi_transfer t[] = {
		{
			.tx_buf = &st->data[0].d8[0],
			.len = 4,
			.cs_change = 1,
		}, {
			.tx_buf = &st->data[1].d8[0],
			.rx_buf = &st->data[1].d8[0],
			.len = 4,
		},
	};

	tmp = ADS8688_CMD_REG(ADS8688_CMD_REG_MAN_CH(chan));
	tmp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[0].d32 = cpu_to_be32(tmp);

	tmp = ADS8688_CMD_REG(ADS8688_CMD_REG_NOOP);
	tmp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[1].d32 = cpu_to_be32(tmp);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	if (ret < 0)
		return ret;

	return be32_to_cpu(st->data[1].d32) & 0xffff;
}