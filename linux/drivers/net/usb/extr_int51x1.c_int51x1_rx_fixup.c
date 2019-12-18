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
struct usbnet {int /*<<< orphan*/  net; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  INT51X1_HEADER_SIZE ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int int51x1_rx_fixup(struct usbnet *dev, struct sk_buff *skb)
{
	int len;

	if (!(pskb_may_pull(skb, INT51X1_HEADER_SIZE))) {
		netdev_err(dev->net, "unexpected tiny rx frame\n");
		return 0;
	}

	len = le16_to_cpu(*(__le16 *)&skb->data[skb->len - 2]);

	skb_trim(skb, len);

	return 1;
}