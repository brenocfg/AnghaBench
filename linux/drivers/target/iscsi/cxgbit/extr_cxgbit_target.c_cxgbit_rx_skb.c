#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cdev; } ;
struct cxgbit_sock {TYPE_2__ com; } ;
struct cxgb4_lld_info {int /*<<< orphan*/  adapter_type; } ;
struct TYPE_3__ {struct cxgb4_lld_info lldi; } ;

/* Variables and functions */
 int SKCBF_RX_LRO ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int cxgbit_process_lro_skb (struct cxgbit_sock*,struct sk_buff*) ; 
 int cxgbit_rx_lro_skb (struct cxgbit_sock*,struct sk_buff*) ; 
 int cxgbit_skcb_flags (struct sk_buff*) ; 
 scalar_t__ is_t5 (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int cxgbit_rx_skb(struct cxgbit_sock *csk, struct sk_buff *skb)
{
	struct cxgb4_lld_info *lldi = &csk->com.cdev->lldi;
	int ret = -1;

	if (likely(cxgbit_skcb_flags(skb) & SKCBF_RX_LRO)) {
		if (is_t5(lldi->adapter_type))
			ret = cxgbit_rx_lro_skb(csk, skb);
		else
			ret = cxgbit_process_lro_skb(csk, skb);
	}

	__kfree_skb(skb);
	return ret;
}