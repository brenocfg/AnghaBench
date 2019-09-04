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
typedef  int /*<<< orphan*/  u8 ;
struct spi_device {int dummy; } ;
struct mcp251x_priv {int /*<<< orphan*/  spi_tx_buf; } ;

/* Variables and functions */
 scalar_t__ TXBCTRL (int) ; 
 int TXBDAT_OFF ; 
 scalar_t__ mcp251x_is_2510 (struct spi_device*) ; 
 int /*<<< orphan*/  mcp251x_spi_trans (struct spi_device*,int) ; 
 int /*<<< orphan*/  mcp251x_write_reg (struct spi_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void mcp251x_hw_tx_frame(struct spi_device *spi, u8 *buf,
				int len, int tx_buf_idx)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);

	if (mcp251x_is_2510(spi)) {
		int i;

		for (i = 1; i < TXBDAT_OFF + len; i++)
			mcp251x_write_reg(spi, TXBCTRL(tx_buf_idx) + i,
					  buf[i]);
	} else {
		memcpy(priv->spi_tx_buf, buf, TXBDAT_OFF + len);
		mcp251x_spi_trans(spi, TXBDAT_OFF + len);
	}
}