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
typedef  scalar_t__ u32 ;
struct sprd_spi {scalar_t__ trans_len; int trans_mode; int hw_mode; scalar_t__ (* read_bufs ) (struct sprd_spi*,scalar_t__) ;scalar_t__ (* write_bufs ) (struct sprd_spi*,scalar_t__) ;} ;
struct spi_transfer {int dummy; } ;
struct spi_device {int /*<<< orphan*/  controller; } ;

/* Variables and functions */
 int SPI_3WIRE ; 
 int SPI_TX_DUAL ; 
 scalar_t__ SPRD_SPI_FIFO_SIZE ; 
 int SPRD_SPI_RX_MODE ; 
 int SPRD_SPI_TX_MODE ; 
 struct sprd_spi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_spi_enter_idle (struct sprd_spi*) ; 
 int /*<<< orphan*/  sprd_spi_rx_req (struct sprd_spi*) ; 
 int /*<<< orphan*/  sprd_spi_set_rx_length (struct sprd_spi*,scalar_t__) ; 
 int /*<<< orphan*/  sprd_spi_set_tx_length (struct sprd_spi*,scalar_t__) ; 
 int /*<<< orphan*/  sprd_spi_tx_req (struct sprd_spi*) ; 
 int sprd_spi_wait_for_rx_end (struct sprd_spi*,struct spi_transfer*) ; 
 int sprd_spi_wait_for_tx_end (struct sprd_spi*,struct spi_transfer*) ; 
 scalar_t__ stub1 (struct sprd_spi*,scalar_t__) ; 
 scalar_t__ stub2 (struct sprd_spi*,scalar_t__) ; 
 scalar_t__ stub3 (struct sprd_spi*,scalar_t__) ; 

__attribute__((used)) static int sprd_spi_txrx_bufs(struct spi_device *sdev, struct spi_transfer *t)
{
	struct sprd_spi *ss = spi_controller_get_devdata(sdev->controller);
	u32 trans_len = ss->trans_len, len;
	int ret, write_size = 0, read_size = 0;

	while (trans_len) {
		len = trans_len > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE :
			trans_len;
		if (ss->trans_mode & SPRD_SPI_TX_MODE) {
			sprd_spi_set_tx_length(ss, len);
			write_size += ss->write_bufs(ss, len);

			/*
			 * For our 3 wires mode or dual TX line mode, we need
			 * to request the controller to transfer.
			 */
			if (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
				sprd_spi_tx_req(ss);

			ret = sprd_spi_wait_for_tx_end(ss, t);
		} else {
			sprd_spi_set_rx_length(ss, len);

			/*
			 * For our 3 wires mode or dual TX line mode, we need
			 * to request the controller to read.
			 */
			if (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
				sprd_spi_rx_req(ss);
			else
				write_size += ss->write_bufs(ss, len);

			ret = sprd_spi_wait_for_rx_end(ss, t);
		}

		if (ret)
			goto complete;

		if (ss->trans_mode & SPRD_SPI_RX_MODE)
			read_size += ss->read_bufs(ss, len);

		trans_len -= len;
	}

	if (ss->trans_mode & SPRD_SPI_TX_MODE)
		ret = write_size;
	else
		ret = read_size;
complete:
	sprd_spi_enter_idle(ss);

	return ret;
}