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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct spi_transfer {int bits_per_word; int len; int cs_change; int /*<<< orphan*/ * rx_buf; int /*<<< orphan*/ * tx_buf; } ;
struct iio_dev {int dummy; } ;
struct adxrs450_state {int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  rx; TYPE_1__* us; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADXRS450_P ; 
 int ADXRS450_READ_DATA ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct spi_transfer*) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hweight32 (int) ; 
 struct adxrs450_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_sync_transfer (TYPE_1__*,struct spi_transfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adxrs450_spi_read_reg_16(struct iio_dev *indio_dev,
				    u8 reg_address,
				    u16 *val)
{
	struct adxrs450_state *st = iio_priv(indio_dev);
	u32 tx;
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = &st->tx,
			.bits_per_word = 8,
			.len = sizeof(st->tx),
			.cs_change = 1,
		}, {
			.rx_buf = &st->rx,
			.bits_per_word = 8,
			.len = sizeof(st->rx),
		},
	};

	mutex_lock(&st->buf_lock);
	tx = ADXRS450_READ_DATA | (reg_address << 17);

	if (!(hweight32(tx) & 1))
		tx |= ADXRS450_P;

	st->tx = cpu_to_be32(tx);
	ret = spi_sync_transfer(st->us, xfers, ARRAY_SIZE(xfers));
	if (ret) {
		dev_err(&st->us->dev, "problem while reading 16 bit register 0x%02x\n",
				reg_address);
		goto error_ret;
	}

	*val = (be32_to_cpu(st->rx) >> 5) & 0xFFFF;

error_ret:
	mutex_unlock(&st->buf_lock);
	return ret;
}