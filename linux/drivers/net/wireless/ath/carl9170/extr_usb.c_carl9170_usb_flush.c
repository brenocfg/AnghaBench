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
struct urb {scalar_t__ context; } ;
struct sk_buff {int dummy; } ;
struct ar9170 {int /*<<< orphan*/  tx_anch; int /*<<< orphan*/  tx_cmd; int /*<<< orphan*/  tx_wait; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  carl9170_tx_callback (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_tx_drop (struct ar9170*,struct sk_buff*) ; 
 int /*<<< orphan*/  carl9170_usb_handle_tx_err (struct ar9170*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 struct urb* usb_get_from_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_wait_anchor_empty_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int carl9170_usb_flush(struct ar9170 *ar)
{
	struct urb *urb;
	int ret, err = 0;

	while ((urb = usb_get_from_anchor(&ar->tx_wait))) {
		struct sk_buff *skb = (void *)urb->context;
		carl9170_tx_drop(ar, skb);
		carl9170_tx_callback(ar, skb);
		usb_free_urb(urb);
	}

	ret = usb_wait_anchor_empty_timeout(&ar->tx_cmd, 1000);
	if (ret == 0)
		err = -ETIMEDOUT;

	/* lets wait a while until the tx - queues are dried out */
	ret = usb_wait_anchor_empty_timeout(&ar->tx_anch, 1000);
	if (ret == 0)
		err = -ETIMEDOUT;

	usb_kill_anchored_urbs(&ar->tx_anch);
	carl9170_usb_handle_tx_err(ar);

	return err;
}