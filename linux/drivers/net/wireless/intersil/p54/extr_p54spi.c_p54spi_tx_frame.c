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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct p54s_priv {int /*<<< orphan*/  hw; TYPE_1__* spi; } ;
struct p54_hdr {int /*<<< orphan*/  req_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 scalar_t__ FREE_AFTER_TX (struct sk_buff*) ; 
 int /*<<< orphan*/  SPI_ADRS_HOST_INTERRUPTS ; 
 int /*<<< orphan*/  SPI_HOST_INT_WR_READY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  p54_free_skb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  p54spi_int_ack (struct p54s_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_sleep (struct p54s_priv*) ; 
 int p54spi_spi_write_dma (struct p54s_priv*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p54spi_wait_bit (struct p54s_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ p54spi_wakeup (struct p54s_priv*) ; 

__attribute__((used)) static int p54spi_tx_frame(struct p54s_priv *priv, struct sk_buff *skb)
{
	struct p54_hdr *hdr = (struct p54_hdr *) skb->data;
	int ret = 0;

	if (p54spi_wakeup(priv) < 0)
		return -EBUSY;

	ret = p54spi_spi_write_dma(priv, hdr->req_id, skb->data, skb->len);
	if (ret < 0)
		goto out;

	if (!p54spi_wait_bit(priv, SPI_ADRS_HOST_INTERRUPTS,
			     SPI_HOST_INT_WR_READY)) {
		dev_err(&priv->spi->dev, "WR_READY timeout\n");
		ret = -EAGAIN;
		goto out;
	}

	p54spi_int_ack(priv, SPI_HOST_INT_WR_READY);

	if (FREE_AFTER_TX(skb))
		p54_free_skb(priv->hw, skb);
out:
	p54spi_sleep(priv);
	return ret;
}