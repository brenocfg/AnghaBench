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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct opa_vnic_skb_mdata {scalar_t__ flags; int /*<<< orphan*/  entropy; int /*<<< orphan*/  vl; } ;
struct TYPE_4__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  vesw_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  encap_slid; } ;
struct __opa_veswport_info {TYPE_2__ vesw; TYPE_1__ vport; } ;
struct opa_vnic_adapter {struct __opa_veswport_info info; } ;

/* Variables and functions */
 int OPA_VNIC_HDR_LEN ; 
 int /*<<< orphan*/  OPA_VNIC_L4_ETHR ; 
 scalar_t__ OPA_VNIC_SKB_MDATA_ENCAP_ERR ; 
 int /*<<< orphan*/  opa_vnic_calc_entropy (struct sk_buff*) ; 
 int /*<<< orphan*/  opa_vnic_get_def_port (struct opa_vnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_vnic_get_dlid (struct opa_vnic_adapter*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_vnic_get_rc (struct __opa_veswport_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  opa_vnic_get_sc (struct __opa_veswport_info*,struct sk_buff*) ; 
 int /*<<< orphan*/  opa_vnic_get_vl (struct opa_vnic_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  opa_vnic_make_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opa_vnic_wire_length (struct sk_buff*) ; 
 void* skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

void opa_vnic_encap_skb(struct opa_vnic_adapter *adapter, struct sk_buff *skb)
{
	struct __opa_veswport_info *info = &adapter->info;
	struct opa_vnic_skb_mdata *mdata;
	u8 def_port, sc, rc, entropy, *hdr;
	u16 len, l4_hdr;
	u32 dlid;

	hdr = skb_push(skb, OPA_VNIC_HDR_LEN);

	entropy = opa_vnic_calc_entropy(skb);
	def_port = opa_vnic_get_def_port(adapter, entropy);
	len = opa_vnic_wire_length(skb);
	dlid = opa_vnic_get_dlid(adapter, skb, def_port);
	sc = opa_vnic_get_sc(info, skb);
	rc = opa_vnic_get_rc(info, skb);
	l4_hdr = info->vesw.vesw_id;

	mdata = skb_push(skb, sizeof(*mdata));
	mdata->vl = opa_vnic_get_vl(adapter, skb);
	mdata->entropy = entropy;
	mdata->flags = 0;
	if (unlikely(!dlid)) {
		mdata->flags = OPA_VNIC_SKB_MDATA_ENCAP_ERR;
		return;
	}

	opa_vnic_make_header(hdr, info->vport.encap_slid, dlid, len,
			     info->vesw.pkey, entropy, sc, rc,
			     OPA_VNIC_L4_ETHR, l4_hdr);
}