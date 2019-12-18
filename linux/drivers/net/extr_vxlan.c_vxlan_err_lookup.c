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
struct vxlanhdr {int vx_flags; int /*<<< orphan*/  vx_vni; } ;
struct vxlan_sock {int dummy; } ;
struct vxlan_dev {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int VXLAN_HF_VNI ; 
 scalar_t__ VXLAN_HLEN ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,scalar_t__) ; 
 struct vxlan_sock* rcu_dereference_sk_user_data (struct sock*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 
 struct vxlanhdr* vxlan_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  vxlan_vni (int /*<<< orphan*/ ) ; 
 struct vxlan_dev* vxlan_vs_find_vni (struct vxlan_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxlan_err_lookup(struct sock *sk, struct sk_buff *skb)
{
	struct vxlan_dev *vxlan;
	struct vxlan_sock *vs;
	struct vxlanhdr *hdr;
	__be32 vni;

	if (!pskb_may_pull(skb, skb_transport_offset(skb) + VXLAN_HLEN))
		return -EINVAL;

	hdr = vxlan_hdr(skb);

	if (!(hdr->vx_flags & VXLAN_HF_VNI))
		return -EINVAL;

	vs = rcu_dereference_sk_user_data(sk);
	if (!vs)
		return -ENOENT;

	vni = vxlan_vni(hdr->vx_vni);
	vxlan = vxlan_vs_find_vni(vs, skb->dev->ifindex, vni);
	if (!vxlan)
		return -ENOENT;

	return 0;
}