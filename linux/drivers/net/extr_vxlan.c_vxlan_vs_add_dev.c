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
struct vxlan_sock {int dummy; } ;
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct vxlan_dev_node {int /*<<< orphan*/  hlist; struct vxlan_dev* vxlan; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_vni; } ;
struct vxlan_dev {TYPE_1__ default_dst; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vni_head (struct vxlan_sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_net_id ; 

__attribute__((used)) static void vxlan_vs_add_dev(struct vxlan_sock *vs, struct vxlan_dev *vxlan,
			     struct vxlan_dev_node *node)
{
	struct vxlan_net *vn = net_generic(vxlan->net, vxlan_net_id);
	__be32 vni = vxlan->default_dst.remote_vni;

	node->vxlan = vxlan;
	spin_lock(&vn->sock_lock);
	hlist_add_head_rcu(&node->hlist, vni_head(vs, vni));
	spin_unlock(&vn->sock_lock);
}