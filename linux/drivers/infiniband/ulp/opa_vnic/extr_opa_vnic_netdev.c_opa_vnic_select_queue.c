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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct opa_vnic_skb_mdata {int /*<<< orphan*/  vl; int /*<<< orphan*/  entropy; } ;
struct opa_vnic_adapter {TYPE_1__* rn_ops; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* ndo_select_queue ) (struct net_device*,struct sk_buff*,struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  opa_vnic_calc_entropy (struct sk_buff*) ; 
 int /*<<< orphan*/  opa_vnic_get_vl (struct opa_vnic_adapter*,struct sk_buff*) ; 
 struct opa_vnic_adapter* opa_vnic_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 struct opa_vnic_skb_mdata* skb_push (struct sk_buff*,int) ; 
 int stub1 (struct net_device*,struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static u16 opa_vnic_select_queue(struct net_device *netdev, struct sk_buff *skb,
				 struct net_device *sb_dev)
{
	struct opa_vnic_adapter *adapter = opa_vnic_priv(netdev);
	struct opa_vnic_skb_mdata *mdata;
	int rc;

	/* pass entropy and vl as metadata in skb */
	mdata = skb_push(skb, sizeof(*mdata));
	mdata->entropy = opa_vnic_calc_entropy(skb);
	mdata->vl = opa_vnic_get_vl(adapter, skb);
	rc = adapter->rn_ops->ndo_select_queue(netdev, skb, sb_dev);
	skb_pull(skb, sizeof(*mdata));
	return rc;
}