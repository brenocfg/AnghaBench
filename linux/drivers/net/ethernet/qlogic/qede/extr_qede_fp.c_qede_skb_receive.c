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
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct qede_rx_queue {int dummy; } ;
struct qede_fastpath {int /*<<< orphan*/  napi; } ;
struct qede_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static inline void qede_skb_receive(struct qede_dev *edev,
				    struct qede_fastpath *fp,
				    struct qede_rx_queue *rxq,
				    struct sk_buff *skb, u16 vlan_tag)
{
	if (vlan_tag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);

	napi_gro_receive(&fp->napi, skb);
}