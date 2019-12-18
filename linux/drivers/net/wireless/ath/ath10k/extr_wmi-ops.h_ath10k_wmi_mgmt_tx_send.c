#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct ath10k {TYPE_3__ wmi; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  mgmt_tx_send_cmdid; } ;
struct TYPE_4__ {struct sk_buff* (* gen_mgmt_tx_send ) (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
ath10k_wmi_mgmt_tx_send(struct ath10k *ar, struct sk_buff *msdu,
			dma_addr_t paddr)
{
	struct sk_buff *skb;
	int ret;

	if (!ar->wmi.ops->gen_mgmt_tx_send)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_mgmt_tx_send(ar, msdu, paddr);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	ret = ath10k_wmi_cmd_send(ar, skb,
				  ar->wmi.cmd->mgmt_tx_send_cmdid);
	if (ret)
		return ret;

	return 0;
}