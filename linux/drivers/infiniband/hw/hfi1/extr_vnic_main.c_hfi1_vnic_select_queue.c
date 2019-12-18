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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct sdma_engine {int /*<<< orphan*/  this_idx; } ;
struct opa_vnic_skb_mdata {int /*<<< orphan*/  vl; int /*<<< orphan*/  entropy; } ;
struct net_device {int dummy; } ;
struct hfi1_vnic_vport_info {int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 struct hfi1_vnic_vport_info* opa_vnic_dev_priv (struct net_device*) ; 
 struct sdma_engine* sdma_select_engine_vl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 hfi1_vnic_select_queue(struct net_device *netdev,
				  struct sk_buff *skb,
				  struct net_device *sb_dev)
{
	struct hfi1_vnic_vport_info *vinfo = opa_vnic_dev_priv(netdev);
	struct opa_vnic_skb_mdata *mdata;
	struct sdma_engine *sde;

	mdata = (struct opa_vnic_skb_mdata *)skb->data;
	sde = sdma_select_engine_vl(vinfo->dd, mdata->entropy, mdata->vl);
	return sde->this_idx;
}