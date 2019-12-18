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
typedef  void* u8 ;
struct spi_device {int dummy; } ;
struct hi3110_priv {void** spi_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  hi3110_spi_trans (struct spi_device*,int) ; 
 struct hi3110_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void hi3110_write(struct spi_device *spi, u8 reg, u8 val)
{
	struct hi3110_priv *priv = spi_get_drvdata(spi);

	priv->spi_tx_buf[0] = reg;
	priv->spi_tx_buf[1] = val;
	hi3110_spi_trans(spi, 2);
}