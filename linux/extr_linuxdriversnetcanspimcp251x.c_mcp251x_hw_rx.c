#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;
struct sk_buff {int dummy; } ;
struct mcp251x_priv {TYPE_2__* net; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 int CAN_RTR_FLAG ; 
 int RXBDAT_OFF ; 
 int RXBDLC_LEN_MASK ; 
 size_t RXBDLC_OFF ; 
 int RXBDLC_RTR ; 
 size_t RXBEID0_OFF ; 
 size_t RXBEID8_OFF ; 
 size_t RXBSIDH_OFF ; 
 int RXBSIDH_SHIFT ; 
 int RXBSIDL_EID ; 
 int RXBSIDL_IDE ; 
 size_t RXBSIDL_OFF ; 
 int RXBSIDL_SHIFT ; 
 int RXBSIDL_SRR ; 
 int SET_BYTE (int,int) ; 
 int SPI_TRANSFER_BUF_LEN ; 
 struct sk_buff* alloc_can_skb (TYPE_2__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_led_event (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ get_can_dlc (int) ; 
 int /*<<< orphan*/  mcp251x_hw_rx_frame (struct spi_device*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  netif_rx_ni (struct sk_buff*) ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static void mcp251x_hw_rx(struct spi_device *spi, int buf_idx)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);
	struct sk_buff *skb;
	struct can_frame *frame;
	u8 buf[SPI_TRANSFER_BUF_LEN];

	skb = alloc_can_skb(priv->net, &frame);
	if (!skb) {
		dev_err(&spi->dev, "cannot allocate RX skb\n");
		priv->net->stats.rx_dropped++;
		return;
	}

	mcp251x_hw_rx_frame(spi, buf, buf_idx);
	if (buf[RXBSIDL_OFF] & RXBSIDL_IDE) {
		/* Extended ID format */
		frame->can_id = CAN_EFF_FLAG;
		frame->can_id |=
			/* Extended ID part */
			SET_BYTE(buf[RXBSIDL_OFF] & RXBSIDL_EID, 2) |
			SET_BYTE(buf[RXBEID8_OFF], 1) |
			SET_BYTE(buf[RXBEID0_OFF], 0) |
			/* Standard ID part */
			(((buf[RXBSIDH_OFF] << RXBSIDH_SHIFT) |
			  (buf[RXBSIDL_OFF] >> RXBSIDL_SHIFT)) << 18);
		/* Remote transmission request */
		if (buf[RXBDLC_OFF] & RXBDLC_RTR)
			frame->can_id |= CAN_RTR_FLAG;
	} else {
		/* Standard ID format */
		frame->can_id =
			(buf[RXBSIDH_OFF] << RXBSIDH_SHIFT) |
			(buf[RXBSIDL_OFF] >> RXBSIDL_SHIFT);
		if (buf[RXBSIDL_OFF] & RXBSIDL_SRR)
			frame->can_id |= CAN_RTR_FLAG;
	}
	/* Data length */
	frame->can_dlc = get_can_dlc(buf[RXBDLC_OFF] & RXBDLC_LEN_MASK);
	memcpy(frame->data, buf + RXBDAT_OFF, frame->can_dlc);

	priv->net->stats.rx_packets++;
	priv->net->stats.rx_bytes += frame->can_dlc;

	can_led_event(priv->net, CAN_LED_EVENT_RX);

	netif_rx_ni(skb);
}