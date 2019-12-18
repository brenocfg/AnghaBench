#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_transfer {unsigned int* tx_buf; int bits_per_word; int len; int cs_change; int /*<<< orphan*/  delay_usecs; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  cs_change_delay_unit; int /*<<< orphan*/  cs_change_delay; } ;
struct spi_message {int dummy; } ;
struct adis {unsigned int* tx; unsigned int current_page; int /*<<< orphan*/  txrx_lock; int /*<<< orphan*/  rx; TYPE_2__* spi; TYPE_1__* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_delay; int /*<<< orphan*/  cs_change_delay; int /*<<< orphan*/  write_delay; } ;

/* Variables and functions */
 unsigned int ADIS_PAGE_SIZE ; 
 void* ADIS_READ_REG (unsigned int) ; 
 int /*<<< orphan*/  ADIS_REG_PAGE_ID ; 
 unsigned int ADIS_WRITE_REG (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SPI_DELAY_UNIT_USECS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 unsigned int get_unaligned_be16 (int /*<<< orphan*/ ) ; 
 unsigned int get_unaligned_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_2__*,struct spi_message*) ; 

int adis_read_reg(struct adis *adis, unsigned int reg,
	unsigned int *val, unsigned int size)
{
	unsigned int page = reg / ADIS_PAGE_SIZE;
	struct spi_message msg;
	int ret;
	struct spi_transfer xfers[] = {
		{
			.tx_buf = adis->tx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay_usecs = adis->data->write_delay,
			.cs_change_delay = adis->data->cs_change_delay,
			.cs_change_delay_unit = SPI_DELAY_UNIT_USECS,
		}, {
			.tx_buf = adis->tx + 2,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay_usecs = adis->data->read_delay,
			.cs_change_delay = adis->data->cs_change_delay,
			.cs_change_delay_unit = SPI_DELAY_UNIT_USECS,
		}, {
			.tx_buf = adis->tx + 4,
			.rx_buf = adis->rx,
			.bits_per_word = 8,
			.len = 2,
			.cs_change = 1,
			.delay_usecs = adis->data->read_delay,
			.cs_change_delay = adis->data->cs_change_delay,
			.cs_change_delay_unit = SPI_DELAY_UNIT_USECS,
		}, {
			.rx_buf = adis->rx + 2,
			.bits_per_word = 8,
			.len = 2,
			.delay_usecs = adis->data->read_delay,
		},
	};

	mutex_lock(&adis->txrx_lock);
	spi_message_init(&msg);

	if (adis->current_page != page) {
		adis->tx[0] = ADIS_WRITE_REG(ADIS_REG_PAGE_ID);
		adis->tx[1] = page;
		spi_message_add_tail(&xfers[0], &msg);
	}

	switch (size) {
	case 4:
		adis->tx[2] = ADIS_READ_REG(reg + 2);
		adis->tx[3] = 0;
		spi_message_add_tail(&xfers[1], &msg);
		/* fall through */
	case 2:
		adis->tx[4] = ADIS_READ_REG(reg);
		adis->tx[5] = 0;
		spi_message_add_tail(&xfers[2], &msg);
		spi_message_add_tail(&xfers[3], &msg);
		break;
	default:
		ret = -EINVAL;
		goto out_unlock;
	}

	ret = spi_sync(adis->spi, &msg);
	if (ret) {
		dev_err(&adis->spi->dev, "Failed to read register 0x%02X: %d\n",
				reg, ret);
		goto out_unlock;
	} else {
		adis->current_page = page;
	}

	switch (size) {
	case 4:
		*val = get_unaligned_be32(adis->rx);
		break;
	case 2:
		*val = get_unaligned_be16(adis->rx + 2);
		break;
	}

out_unlock:
	mutex_unlock(&adis->txrx_lock);

	return ret;
}