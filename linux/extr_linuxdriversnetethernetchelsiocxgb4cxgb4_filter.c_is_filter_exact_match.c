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
typedef  int u64 ;
struct tp_params {int hash_filter_mask; int fcoe_shift; int port_shift; int vnic_shift; int ingress_config; int vlan_shift; int tos_shift; int protocol_shift; int ethertype_shift; int macmatch_shift; int matchtype_shift; int frag_shift; } ;
struct TYPE_6__ {int lport; int fport; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ macidx; scalar_t__ ethtype; scalar_t__ proto; scalar_t__ tos; scalar_t__ ivlan; scalar_t__ ovlan_vld; scalar_t__ pfvf_vld; scalar_t__ iport; scalar_t__ fcoe; int /*<<< orphan*/  lip; int /*<<< orphan*/  fip; scalar_t__ encap_vld; } ;
struct TYPE_4__ {int /*<<< orphan*/  fport; int /*<<< orphan*/  lport; int /*<<< orphan*/  lip; int /*<<< orphan*/  fip; } ;
struct ch_filter_specification {TYPE_3__ mask; TYPE_1__ val; scalar_t__ type; } ;
struct TYPE_5__ {struct tp_params tp; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int VNIC_F ; 
 int /*<<< orphan*/  is_addr_all_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_hashfilter (struct adapter*) ; 
 scalar_t__ is_inaddr_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool is_filter_exact_match(struct adapter *adap,
			   struct ch_filter_specification *fs)
{
	struct tp_params *tp = &adap->params.tp;
	u64 hash_filter_mask = tp->hash_filter_mask;
	u64 ntuple_mask = 0;

	if (!is_hashfilter(adap))
		return false;

	 /* Keep tunnel VNI match disabled for hash-filters for now */
	if (fs->mask.encap_vld)
		return false;

	if (fs->type) {
		if (is_inaddr_any(fs->val.fip, AF_INET6) ||
		    !is_addr_all_mask(fs->mask.fip, AF_INET6))
			return false;

		if (is_inaddr_any(fs->val.lip, AF_INET6) ||
		    !is_addr_all_mask(fs->mask.lip, AF_INET6))
			return false;
	} else {
		if (is_inaddr_any(fs->val.fip, AF_INET) ||
		    !is_addr_all_mask(fs->mask.fip, AF_INET))
			return false;

		if (is_inaddr_any(fs->val.lip, AF_INET) ||
		    !is_addr_all_mask(fs->mask.lip, AF_INET))
			return false;
	}

	if (!fs->val.lport || fs->mask.lport != 0xffff)
		return false;

	if (!fs->val.fport || fs->mask.fport != 0xffff)
		return false;

	/* calculate tuple mask and compare with mask configured in hw */
	if (tp->fcoe_shift >= 0)
		ntuple_mask |= (u64)fs->mask.fcoe << tp->fcoe_shift;

	if (tp->port_shift >= 0)
		ntuple_mask |= (u64)fs->mask.iport << tp->port_shift;

	if (tp->vnic_shift >= 0) {
		if ((adap->params.tp.ingress_config & VNIC_F))
			ntuple_mask |= (u64)fs->mask.pfvf_vld << tp->vnic_shift;
		else
			ntuple_mask |= (u64)fs->mask.ovlan_vld <<
				tp->vnic_shift;
	}

	if (tp->vlan_shift >= 0)
		ntuple_mask |= (u64)fs->mask.ivlan << tp->vlan_shift;

	if (tp->tos_shift >= 0)
		ntuple_mask |= (u64)fs->mask.tos << tp->tos_shift;

	if (tp->protocol_shift >= 0)
		ntuple_mask |= (u64)fs->mask.proto << tp->protocol_shift;

	if (tp->ethertype_shift >= 0)
		ntuple_mask |= (u64)fs->mask.ethtype << tp->ethertype_shift;

	if (tp->macmatch_shift >= 0)
		ntuple_mask |= (u64)fs->mask.macidx << tp->macmatch_shift;

	if (tp->matchtype_shift >= 0)
		ntuple_mask |= (u64)fs->mask.matchtype << tp->matchtype_shift;

	if (tp->frag_shift >= 0)
		ntuple_mask |= (u64)fs->mask.frag << tp->frag_shift;

	if (ntuple_mask != hash_filter_mask)
		return false;

	return true;
}