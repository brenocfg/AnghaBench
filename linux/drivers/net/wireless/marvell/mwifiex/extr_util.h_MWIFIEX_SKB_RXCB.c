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
struct sk_buff {scalar_t__ cb; } ;
struct mwifiex_rxinfo {int dummy; } ;
struct mwifiex_cb {struct mwifiex_rxinfo rx_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline struct mwifiex_rxinfo *MWIFIEX_SKB_RXCB(struct sk_buff *skb)
{
	struct mwifiex_cb *cb = (struct mwifiex_cb *)skb->cb;

	BUILD_BUG_ON(sizeof(struct mwifiex_cb) > sizeof(skb->cb));
	return &cb->rx_info;
}