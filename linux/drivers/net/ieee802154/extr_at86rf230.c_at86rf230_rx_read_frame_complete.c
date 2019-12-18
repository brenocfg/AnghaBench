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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct at86rf230_state_change {int* buf; struct at86rf230_local* lp; } ;
struct at86rf230_local {int /*<<< orphan*/  hw; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IEEE802154_MTU ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ieee802154_is_valid_psdu_len (int) ; 
 int /*<<< orphan*/  ieee802154_rx_irqsafe (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  kfree (struct at86rf230_state_change*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int const*,int) ; 

__attribute__((used)) static void
at86rf230_rx_read_frame_complete(void *context)
{
	struct at86rf230_state_change *ctx = context;
	struct at86rf230_local *lp = ctx->lp;
	const u8 *buf = ctx->buf;
	struct sk_buff *skb;
	u8 len, lqi;

	len = buf[1];
	if (!ieee802154_is_valid_psdu_len(len)) {
		dev_vdbg(&lp->spi->dev, "corrupted frame received\n");
		len = IEEE802154_MTU;
	}
	lqi = buf[2 + len];

	skb = dev_alloc_skb(IEEE802154_MTU);
	if (!skb) {
		dev_vdbg(&lp->spi->dev, "failed to allocate sk_buff\n");
		kfree(ctx);
		return;
	}

	skb_put_data(skb, buf + 2, len);
	ieee802154_rx_irqsafe(lp->hw, skb, lqi);
	kfree(ctx);
}