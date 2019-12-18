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
struct spi_xcomm {int /*<<< orphan*/  i2c; int /*<<< orphan*/ * buf; } ;
struct spi_transfer {int len; scalar_t__ rx_buf; scalar_t__ tx_buf; } ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SPI_XCOMM_CMD_WRITE ; 
 int i2c_master_recv (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int spi_xcomm_txrx_bufs(struct spi_xcomm *spi_xcomm,
	struct spi_device *spi, struct spi_transfer *t)
{
	int ret;

	if (t->tx_buf) {
		spi_xcomm->buf[0] = SPI_XCOMM_CMD_WRITE;
		memcpy(spi_xcomm->buf + 1, t->tx_buf, t->len);

		ret = i2c_master_send(spi_xcomm->i2c, spi_xcomm->buf, t->len + 1);
		if (ret < 0)
			return ret;
		else if (ret != t->len + 1)
			return -EIO;
	} else if (t->rx_buf) {
		ret = i2c_master_recv(spi_xcomm->i2c, t->rx_buf, t->len);
		if (ret < 0)
			return ret;
		else if (ret != t->len)
			return -EIO;
	}

	return t->len;
}