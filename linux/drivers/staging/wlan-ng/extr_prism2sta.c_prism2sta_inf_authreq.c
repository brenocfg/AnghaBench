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
struct wlandevice {struct hfa384x* priv; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct hfa384x_inf_frame {int dummy; } ;
struct hfa384x {int /*<<< orphan*/  link_bh; int /*<<< orphan*/  authq; } ;

/* Variables and functions */
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct hfa384x_inf_frame*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void prism2sta_inf_authreq(struct wlandevice *wlandev,
				  struct hfa384x_inf_frame *inf)
{
	struct hfa384x *hw = wlandev->priv;
	struct sk_buff *skb;

	skb = dev_alloc_skb(sizeof(*inf));
	if (skb) {
		skb_put(skb, sizeof(*inf));
		memcpy(skb->data, inf, sizeof(*inf));
		skb_queue_tail(&hw->authq, skb);
		schedule_work(&hw->link_bh);
	}
}