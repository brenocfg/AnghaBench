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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vxlanhdr {int vx_flags; int /*<<< orphan*/  vx_vni; } ;
struct sk_buff {scalar_t__ remcsum_offload; } ;

/* Variables and functions */
 int VXLAN_F_REMCSUM_NOPARTIAL ; 
 int VXLAN_HF_RCO ; 
 int /*<<< orphan*/  VXLAN_VNI_MASK ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_remcsum_process (struct sk_buff*,void*,size_t,size_t,int) ; 
 scalar_t__ vxlan_hdr (struct sk_buff*) ; 
 size_t vxlan_rco_offset (int /*<<< orphan*/ ) ; 
 size_t vxlan_rco_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vxlan_remcsum(struct vxlanhdr *unparsed,
			  struct sk_buff *skb, u32 vxflags)
{
	size_t start, offset;

	if (!(unparsed->vx_flags & VXLAN_HF_RCO) || skb->remcsum_offload)
		goto out;

	start = vxlan_rco_start(unparsed->vx_vni);
	offset = start + vxlan_rco_offset(unparsed->vx_vni);

	if (!pskb_may_pull(skb, offset + sizeof(u16)))
		return false;

	skb_remcsum_process(skb, (void *)(vxlan_hdr(skb) + 1), start, offset,
			    !!(vxflags & VXLAN_F_REMCSUM_NOPARTIAL));
out:
	unparsed->vx_flags &= ~VXLAN_HF_RCO;
	unparsed->vx_vni &= VXLAN_VNI_MASK;
	return true;
}