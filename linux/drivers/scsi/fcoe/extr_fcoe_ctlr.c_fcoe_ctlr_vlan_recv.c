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
struct sk_buff {scalar_t__ data; } ;
struct fip_header {int fip_subcode; } ;
struct fcoe_rport {int dummy; } ;
struct fcoe_ctlr {int /*<<< orphan*/  ctlr_mutex; } ;
typedef  enum fip_vlan_subcode { ____Placeholder_fip_vlan_subcode } fip_vlan_subcode ;

/* Variables and functions */
 int FIP_SC_VL_REQ ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int) ; 
 int /*<<< orphan*/  fcoe_ctlr_vlan_disc_reply (struct fcoe_ctlr*,struct fcoe_rport*) ; 
 int fcoe_ctlr_vlan_parse (struct fcoe_ctlr*,struct sk_buff*,struct fcoe_rport*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fcoe_ctlr_vlan_recv(struct fcoe_ctlr *fip, struct sk_buff *skb)
{
	struct fip_header *fiph;
	enum fip_vlan_subcode sub;
	struct fcoe_rport frport = { };
	int rc;

	fiph = (struct fip_header *)skb->data;
	sub = fiph->fip_subcode;
	rc = fcoe_ctlr_vlan_parse(fip, skb, &frport);
	if (rc) {
		LIBFCOE_FIP_DBG(fip, "vlan_recv vlan_parse error %d\n", rc);
		goto drop;
	}
	mutex_lock(&fip->ctlr_mutex);
	if (sub == FIP_SC_VL_REQ)
		fcoe_ctlr_vlan_disc_reply(fip, &frport);
	mutex_unlock(&fip->ctlr_mutex);

drop:
	kfree_skb(skb);
	return rc;
}