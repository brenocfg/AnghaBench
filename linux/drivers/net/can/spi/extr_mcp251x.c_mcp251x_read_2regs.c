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
struct mcp251x_priv {int /*<<< orphan*/ * spi_rx_buf; int /*<<< orphan*/ * spi_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSTRUCTION_READ ; 
 int /*<<< orphan*/  mcp251x_spi_trans (struct spi_device*,int) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void mcp251x_read_2regs(struct spi_device *spi, u8 reg, u8 *v1, u8 *v2)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = INSTRUCTION_READ;
	priv->spi_tx_buf[1] = reg;

	mcp251x_spi_trans(spi, 4);

	*v1 = priv->spi_rx_buf[2];
	*v2 = priv->spi_rx_buf[3];
}