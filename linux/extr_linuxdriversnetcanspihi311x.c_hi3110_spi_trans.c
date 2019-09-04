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
struct spi_transfer {int len; int /*<<< orphan*/  rx_dma; int /*<<< orphan*/  tx_dma; int /*<<< orphan*/  cs_change; int /*<<< orphan*/  rx_buf; int /*<<< orphan*/  tx_buf; } ;
struct spi_message {int is_dma_mapped; } ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct hi3110_priv {int /*<<< orphan*/  spi_rx_dma; int /*<<< orphan*/  spi_tx_dma; int /*<<< orphan*/  spi_rx_buf; int /*<<< orphan*/  spi_tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hi3110_enable_dma ; 
 struct hi3110_priv* spi_get_drvdata (struct spi_device*) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (struct spi_device*,struct spi_message*) ; 

__attribute__((used)) static int hi3110_spi_trans(struct spi_device *spi, int len)
{
	struct hi3110_priv *priv = spi_get_drvdata(spi);
	struct spi_transfer t = {
		.tx_buf = priv->spi_tx_buf,
		.rx_buf = priv->spi_rx_buf,
		.len = len,
		.cs_change = 0,
	};
	struct spi_message m;
	int ret;

	spi_message_init(&m);

	if (hi3110_enable_dma) {
		t.tx_dma = priv->spi_tx_dma;
		t.rx_dma = priv->spi_rx_dma;
		m.is_dma_mapped = 1;
	}

	spi_message_add_tail(&t, &m);

	ret = spi_sync(spi, &m);

	if (ret)
		dev_err(&spi->dev, "spi transfer failed: ret = %d\n", ret);
	return ret;
}