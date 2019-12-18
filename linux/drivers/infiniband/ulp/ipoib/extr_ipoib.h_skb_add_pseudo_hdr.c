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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPOIB_HARD_LEN ; 
 int /*<<< orphan*/  IPOIB_PSEUDO_LEN ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 

__attribute__((used)) static inline void skb_add_pseudo_hdr(struct sk_buff *skb)
{
	char *data = skb_push(skb, IPOIB_PSEUDO_LEN);

	/*
	 * only the ipoib header is present now, make room for a dummy
	 * pseudo header and set skb field accordingly
	 */
	memset(data, 0, IPOIB_PSEUDO_LEN);
	skb_reset_mac_header(skb);
	skb_pull(skb, IPOIB_HARD_LEN);
}