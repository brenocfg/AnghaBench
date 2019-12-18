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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct p54s_priv {int /*<<< orphan*/  hw; TYPE_1__* spi; } ;
typedef  int /*<<< orphan*/  rx_head ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 scalar_t__ READAHEAD_SZ ; 
 int /*<<< orphan*/  SPI_ADRS_DMA_DATA ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ p54_rx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  p54spi_sleep (struct p54s_priv*) ; 
 int /*<<< orphan*/  p54spi_spi_read (struct p54s_priv*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 scalar_t__ p54spi_wakeup (struct p54s_priv*) ; 
 scalar_t__* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static int p54spi_rx(struct p54s_priv *priv)
{
	struct sk_buff *skb;
	u16 len;
	u16 rx_head[2];
#define READAHEAD_SZ (sizeof(rx_head)-sizeof(u16))

	if (p54spi_wakeup(priv) < 0)
		return -EBUSY;

	/* Read data size and first data word in one SPI transaction
	 * This is workaround for firmware/DMA bug,
	 * when first data word gets lost under high load.
	 */
	p54spi_spi_read(priv, SPI_ADRS_DMA_DATA, rx_head, sizeof(rx_head));
	len = rx_head[0];

	if (len == 0) {
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "rx request of zero bytes\n");
		return 0;
	}

	/* Firmware may insert up to 4 padding bytes after the lmac header,
	 * but it does not amend the size of SPI data transfer.
	 * Such packets has correct data size in header, thus referencing
	 * past the end of allocated skb. Reserve extra 4 bytes for this case
	 */
	skb = dev_alloc_skb(len + 4);
	if (!skb) {
		p54spi_sleep(priv);
		dev_err(&priv->spi->dev, "could not alloc skb");
		return -ENOMEM;
	}

	if (len <= READAHEAD_SZ) {
		skb_put_data(skb, rx_head + 1, len);
	} else {
		skb_put_data(skb, rx_head + 1, READAHEAD_SZ);
		p54spi_spi_read(priv, SPI_ADRS_DMA_DATA,
				skb_put(skb, len - READAHEAD_SZ),
				len - READAHEAD_SZ);
	}
	p54spi_sleep(priv);
	/* Put additional bytes to compensate for the possible
	 * alignment-caused truncation
	 */
	skb_put(skb, 4);

	if (p54_rx(priv->hw, skb) == 0)
		dev_kfree_skb(skb);

	return 0;
}