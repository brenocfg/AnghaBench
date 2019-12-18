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
typedef  int u8 ;
struct spi_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  spi_rx_buf; int /*<<< orphan*/ * spi_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSTRUCTION_READ_RXB (int) ; 
 scalar_t__ RXBCTRL (int) ; 
 size_t RXBCTRL_OFF ; 
 int RXBDAT_OFF ; 
 int RXBDLC_LEN_MASK ; 
 size_t RXBDLC_OFF ; 
 int /*<<< orphan*/  SPI_TRANSFER_BUF_LEN ; 
 int get_can_dlc (int) ; 
 scalar_t__ mcp251x_is_2510 (struct spi_device*) ; 
 int mcp251x_read_reg (struct spi_device*,scalar_t__) ; 
 int /*<<< orphan*/  mcp251x_spi_trans (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void mcp251x_hw_rx_frame(struct spi_device *spi, u8 *buf,
				int buf_idx)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);

	if (mcp251x_is_2510(spi)) {
		int i, len;

		for (i = 1; i < RXBDAT_OFF; i++)
			buf[i] = mcp251x_read_reg(spi, RXBCTRL(buf_idx) + i);

		len = get_can_dlc(buf[RXBDLC_OFF] & RXBDLC_LEN_MASK);
		for (; i < (RXBDAT_OFF + len); i++)
			buf[i] = mcp251x_read_reg(spi, RXBCTRL(buf_idx) + i);
	} else {
		priv->spi_tx_buf[RXBCTRL_OFF] = INSTRUCTION_READ_RXB(buf_idx);
		mcp251x_spi_trans(spi, SPI_TRANSFER_BUF_LEN);
		memcpy(buf, priv->spi_rx_buf, SPI_TRANSFER_BUF_LEN);
	}
}