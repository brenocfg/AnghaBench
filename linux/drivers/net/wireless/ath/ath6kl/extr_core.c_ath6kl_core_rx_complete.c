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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ath6kl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath6kl_htc_rx_complete (struct ath6kl*,struct sk_buff*,int /*<<< orphan*/ ) ; 

void ath6kl_core_rx_complete(struct ath6kl *ar, struct sk_buff *skb, u8 pipe)
{
	ath6kl_htc_rx_complete(ar, skb, pipe);
}