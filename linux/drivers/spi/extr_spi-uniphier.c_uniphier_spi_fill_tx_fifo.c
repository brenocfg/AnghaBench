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
typedef  int u32 ;
struct uniphier_spi_priv {unsigned int rx_bytes; unsigned int tx_bytes; scalar_t__ base; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int FIELD_PREP (int,unsigned int) ; 
 scalar_t__ SSI_FC ; 
 int SSI_FC_RXFTH_MASK ; 
 int SSI_FC_TXFTH_MASK ; 
 int /*<<< orphan*/  SSI_FIFO_DEPTH ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  uniphier_spi_send (struct uniphier_spi_priv*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void uniphier_spi_fill_tx_fifo(struct uniphier_spi_priv *priv)
{
	unsigned int fifo_threshold, fill_bytes;
	u32 val;

	fifo_threshold = DIV_ROUND_UP(priv->rx_bytes,
				bytes_per_word(priv->bits_per_word));
	fifo_threshold = min(fifo_threshold, SSI_FIFO_DEPTH);

	fill_bytes = fifo_threshold - (priv->rx_bytes - priv->tx_bytes);

	/* set fifo threshold */
	val = readl(priv->base + SSI_FC);
	val &= ~(SSI_FC_TXFTH_MASK | SSI_FC_RXFTH_MASK);
	val |= FIELD_PREP(SSI_FC_TXFTH_MASK, fifo_threshold);
	val |= FIELD_PREP(SSI_FC_RXFTH_MASK, fifo_threshold);
	writel(val, priv->base + SSI_FC);

	while (fill_bytes--)
		uniphier_spi_send(priv);
}