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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct hi3110_priv {int /*<<< orphan*/ * spi_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3110_spi_trans (struct spi_device*,int) ; 
 struct hi3110_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static u8 hi3110_cmd(struct spi_device *spi, u8 command)
{
	struct hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = command;
	dev_dbg(&spi->dev, "hi3110_cmd: %02X\n", command);

	return hi3110_spi_trans(spi, 1);
}