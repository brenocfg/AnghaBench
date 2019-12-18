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
struct sk_buff {int dummy; } ;
struct ath6kl {TYPE_1__* htc_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tx_complete ) (struct ath6kl*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ath6kl*,struct sk_buff*) ; 

__attribute__((used)) static inline void ath6kl_htc_tx_complete(struct ath6kl *ar,
					  struct sk_buff *skb)
{
	ar->htc_ops->tx_complete(ar, skb);
}