#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct iio_dev {int num_channels; } ;
struct adis {int /*<<< orphan*/  msg; TYPE_2__* xfer; scalar_t__* buffer; TYPE_1__* burst; } ;
struct TYPE_6__ {int bits_per_word; int len; scalar_t__* rx_buf; scalar_t__* tx_buf; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg_cmd; scalar_t__ extra_len; } ;

/* Variables and functions */
 scalar_t__ ADIS_READ_REG (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct adis* iio_device_get_drvdata (struct iio_dev*) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 scalar_t__* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adis_update_scan_mode_burst(struct iio_dev *indio_dev,
	const unsigned long *scan_mask)
{
	struct adis *adis = iio_device_get_drvdata(indio_dev);
	unsigned int burst_length;
	u8 *tx;

	/* All but the timestamp channel */
	burst_length = (indio_dev->num_channels - 1) * sizeof(u16);
	burst_length += adis->burst->extra_len;

	adis->xfer = kcalloc(2, sizeof(*adis->xfer), GFP_KERNEL);
	if (!adis->xfer)
		return -ENOMEM;

	adis->buffer = kzalloc(burst_length + sizeof(u16), GFP_KERNEL);
	if (!adis->buffer) {
		kfree(adis->xfer);
		adis->xfer = NULL;
		return -ENOMEM;
	}

	tx = adis->buffer + burst_length;
	tx[0] = ADIS_READ_REG(adis->burst->reg_cmd);
	tx[1] = 0;

	adis->xfer[0].tx_buf = tx;
	adis->xfer[0].bits_per_word = 8;
	adis->xfer[0].len = 2;
	adis->xfer[1].rx_buf = adis->buffer;
	adis->xfer[1].bits_per_word = 8;
	adis->xfer[1].len = burst_length;

	spi_message_init(&adis->msg);
	spi_message_add_tail(&adis->xfer[0], &adis->msg);
	spi_message_add_tail(&adis->xfer[1], &adis->msg);

	return 0;
}