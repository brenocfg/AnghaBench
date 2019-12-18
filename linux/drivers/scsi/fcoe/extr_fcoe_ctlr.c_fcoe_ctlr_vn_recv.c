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
struct sk_buff {scalar_t__ data; } ;
struct fip_header {int fip_subcode; } ;
struct fcoe_rport {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; TYPE_1__* lp; } ;
typedef  enum fip_vn2vn_subcode { ____Placeholder_fip_vn2vn_subcode } fip_vn2vn_subcode ;
struct TYPE_2__ {int vlan; } ;

/* Variables and functions */
 int EAGAIN ; 
#define  FIP_SC_VN_BEACON 132 
#define  FIP_SC_VN_CLAIM_NOTIFY 131 
#define  FIP_SC_VN_CLAIM_REP 130 
#define  FIP_SC_VN_PROBE_REP 129 
#define  FIP_SC_VN_PROBE_REQ 128 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int,...) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_beacon (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_claim_notify (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_claim_resp (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int fcoe_ctlr_vn_parse (struct fcoe_ctlr*,struct sk_buff*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_probe_reply (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  fcoe_ctlr_vn_probe_req (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int skb_vlan_tag_get_id (struct sk_buff*) ; 

__attribute__((used)) static int fcoe_ctlr_vn_recv(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	struct fip_header *fiph;
	enum fip_vn2vn_subcode sub;
	struct fcoe_rport frport = { };
	int rc, vlan_id = 0;

	fiph = (struct fip_header *)skb->data;
	sub = fiph->fip_subcode;

	if (fip->lp->vlan)
		vlan_id = skb_vlan_tag_get_id(skb);

	if (vlan_id && vlan_id != fip->lp->vlan) {
		LIBFCOE_FIP_DBG(fip, "vn_recv drop frame sub %x vlan %d\n",
				sub, vlan_id);
		rc = -EAGAIN;
		goto drop;
	}

	rc = fcoe_ctlr_vn_parse(fip, skb, &frport);
	if (rc) {
		LIBFCOE_FIP_DBG(fip, "vn_recv vn_parse error %d\n", rc);
		goto drop;
	}

	mutex_lock(&fip->ctlr_mutex);
	switch (sub) {
	case FIP_SC_VN_PROBE_REQ:
		fcoe_ctlr_vn_probe_req(fip, &frport);
		break;
	case FIP_SC_VN_PROBE_REP:
		fcoe_ctlr_vn_probe_reply(fip, &frport);
		break;
	case FIP_SC_VN_CLAIM_NOTIFY:
		fcoe_ctlr_vn_claim_notify(fip, &frport);
		break;
	case FIP_SC_VN_CLAIM_REP:
		fcoe_ctlr_vn_claim_resp(fip, &frport);
		break;
	case FIP_SC_VN_BEACON:
		fcoe_ctlr_vn_beacon(fip, &frport);
		break;
	default:
		LIBFCOE_FIP_DBG(fip, "vn_recv unknown subcode %d\n", sub);
		rc = -1;
		break;
	}
	mutex_unlock(&fip->ctlr_mutex);
drop:
	kfree_skb(skb);
	return rc;
}