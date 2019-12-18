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
typedef  int /*<<< orphan*/  xfer ;
typedef  int /*<<< orphan*/  u16 ;
struct spi_transfer {int speed_hz; unsigned int len; int /*<<< orphan*/ * tx_buf; } ;
struct rc_dev {struct ir_spi_data* priv; } ;
struct ir_spi_data {unsigned int freq; int /*<<< orphan*/  regulator; TYPE_1__* spi; int /*<<< orphan*/ * tx_buf; int /*<<< orphan*/  pulse; int /*<<< orphan*/  space; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST (unsigned int,int) ; 
 int EINVAL ; 
 unsigned int IR_SPI_MAX_BUFSIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (struct spi_transfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int spi_sync_transfer (TYPE_1__*,struct spi_transfer*,int) ; 

__attribute__((used)) static int ir_spi_tx(struct rc_dev *dev,
		     unsigned int *buffer, unsigned int count)
{
	int i;
	int ret;
	unsigned int len = 0;
	struct ir_spi_data *idata = dev->priv;
	struct spi_transfer xfer;

	/* convert the pulse/space signal to raw binary signal */
	for (i = 0; i < count; i++) {
		unsigned int periods;
		int j;
		u16 val;

		periods = DIV_ROUND_CLOSEST(buffer[i] * idata->freq, 1000000);

		if (len + periods >= IR_SPI_MAX_BUFSIZE)
			return -EINVAL;

		/*
		 * the first value in buffer is a pulse, so that 0, 2, 4, ...
		 * contain a pulse duration. On the contrary, 1, 3, 5, ...
		 * contain a space duration.
		 */
		val = (i % 2) ? idata->space : idata->pulse;
		for (j = 0; j < periods; j++)
			idata->tx_buf[len++] = val;
	}

	memset(&xfer, 0, sizeof(xfer));

	xfer.speed_hz = idata->freq * 16;
	xfer.len = len * sizeof(*idata->tx_buf);
	xfer.tx_buf = idata->tx_buf;

	ret = regulator_enable(idata->regulator);
	if (ret)
		return ret;

	ret = spi_sync_transfer(idata->spi, &xfer, 1);
	if (ret)
		dev_err(&idata->spi->dev, "unable to deliver the signal\n");

	regulator_disable(idata->regulator);

	return ret ? ret : count;
}