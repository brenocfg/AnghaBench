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
struct spi_transfer {int* tx_buf; int* rx_buf; int /*<<< orphan*/  len; } ;
struct spi_message {int dummy; } ;
struct cc2520_private {int* buf; int /*<<< orphan*/  buffer_mutex; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (TYPE_1__*,struct spi_message*) ; 

__attribute__((used)) static int
cc2520_cmd_strobe(struct cc2520_private *priv, u8 cmd)
{
	int ret;
	u8 status = 0xff;
	struct spi_message msg;
	struct spi_transfer xfer = {
		.len = 0,
		.tx_buf = priv->buf,
		.rx_buf = priv->buf,
	};

	spi_message_init(&msg);
	spi_message_add_tail(&xfer, &msg);

	mutex_lock(&priv->buffer_mutex);
	priv->buf[xfer.len++] = cmd;
	dev_vdbg(&priv->spi->dev,
		 "command strobe buf[0] = %02x\n",
		 priv->buf[0]);

	ret = spi_sync(priv->spi, &msg);
	if (!ret)
		status = priv->buf[0];
	dev_vdbg(&priv->spi->dev,
		 "buf[0] = %02x\n", priv->buf[0]);
	mutex_unlock(&priv->buffer_mutex);

	return ret;
}