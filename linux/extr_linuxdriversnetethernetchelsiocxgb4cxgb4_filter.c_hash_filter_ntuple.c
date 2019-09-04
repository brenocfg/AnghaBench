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
struct tp_params {int vlan_shift; int port_shift; int protocol_shift; int tos_shift; int vnic_shift; int ingress_config; int macmatch_shift; int ethertype_shift; int matchtype_shift; int frag_shift; int fcoe_shift; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int ivlan; int encap_vld; int ovlan; int pfvf_vld; int pf; int vf; int ovlan_vld; scalar_t__ fcoe; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ tos; scalar_t__ proto; scalar_t__ iport; } ;
struct TYPE_5__ {scalar_t__ fcoe; scalar_t__ frag; scalar_t__ matchtype; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ pfvf_vld; scalar_t__ encap_vld; scalar_t__ tos; scalar_t__ iport; scalar_t__ ivlan; } ;
struct ch_filter_specification {TYPE_3__ val; TYPE_2__ mask; } ;
struct TYPE_4__ {struct tp_params tp; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int FT_VLAN_VLD_F ; 
 scalar_t__ IPPROTO_TCP ; 
 int USE_ENC_IDX_F ; 
 int VNIC_F ; 
 struct adapter* netdev2adap (struct net_device*) ; 

__attribute__((used)) static u64 hash_filter_ntuple(struct ch_filter_specification *fs,
			      struct net_device *dev)
{
	struct adapter *adap = netdev2adap(dev);
	struct tp_params *tp = &adap->params.tp;
	u64 ntuple = 0;

	/* Initialize each of the fields which we care about which are present
	 * in the Compressed Filter Tuple.
	 */
	if (tp->vlan_shift >= 0 && fs->mask.ivlan)
		ntuple |= (FT_VLAN_VLD_F | fs->val.ivlan) << tp->vlan_shift;

	if (tp->port_shift >= 0 && fs->mask.iport)
		ntuple |= (u64)fs->val.iport << tp->port_shift;

	if (tp->protocol_shift >= 0) {
		if (!fs->val.proto)
			ntuple |= (u64)IPPROTO_TCP << tp->protocol_shift;
		else
			ntuple |= (u64)fs->val.proto << tp->protocol_shift;
	}

	if (tp->tos_shift >= 0 && fs->mask.tos)
		ntuple |= (u64)(fs->val.tos) << tp->tos_shift;

	if (tp->vnic_shift >= 0) {
		if ((adap->params.tp.ingress_config & USE_ENC_IDX_F) &&
		    fs->mask.encap_vld)
			ntuple |= (u64)((fs->val.encap_vld << 16) |
					(fs->val.ovlan)) << tp->vnic_shift;
		else if ((adap->params.tp.ingress_config & VNIC_F) &&
			 fs->mask.pfvf_vld)
			ntuple |= (u64)((fs->val.pfvf_vld << 16) |
					(fs->val.pf << 13) |
					(fs->val.vf)) << tp->vnic_shift;
		else
			ntuple |= (u64)((fs->val.ovlan_vld << 16) |
					(fs->val.ovlan)) << tp->vnic_shift;
	}

	if (tp->macmatch_shift >= 0 && fs->mask.macidx)
		ntuple |= (u64)(fs->val.macidx) << tp->macmatch_shift;

	if (tp->ethertype_shift >= 0 && fs->mask.ethtype)
		ntuple |= (u64)(fs->val.ethtype) << tp->ethertype_shift;

	if (tp->matchtype_shift >= 0 && fs->mask.matchtype)
		ntuple |= (u64)(fs->val.matchtype) << tp->matchtype_shift;

	if (tp->frag_shift >= 0 && fs->mask.frag)
		ntuple |= (u64)(fs->val.frag) << tp->frag_shift;

	if (tp->fcoe_shift >= 0 && fs->mask.fcoe)
		ntuple |= (u64)(fs->val.fcoe) << tp->fcoe_shift;
	return ntuple;
}