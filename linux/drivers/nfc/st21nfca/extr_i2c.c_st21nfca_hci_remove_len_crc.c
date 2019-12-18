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
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST21NFCA_FRAME_HEADROOM ; 
 scalar_t__ ST21NFCA_FRAME_TAILROOM ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static void st21nfca_hci_remove_len_crc(struct sk_buff *skb)
{
	skb_pull(skb, ST21NFCA_FRAME_HEADROOM);
	skb_trim(skb, skb->len - ST21NFCA_FRAME_TAILROOM);
}