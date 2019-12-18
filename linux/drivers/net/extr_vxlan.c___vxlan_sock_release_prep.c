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
struct vxlan_sock {int flags; TYPE_1__* sock; int /*<<< orphan*/  hlist; int /*<<< orphan*/  refcnt; } ;
struct vxlan_net {int /*<<< orphan*/  sock_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDP_TUNNEL_TYPE_VXLAN ; 
 int /*<<< orphan*/  UDP_TUNNEL_TYPE_VXLAN_GPE ; 
 int VXLAN_F_GPE ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 struct vxlan_net* net_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udp_tunnel_notify_del_rx_port (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxlan_net_id ; 

__attribute__((used)) static bool __vxlan_sock_release_prep(struct vxlan_sock *vs)
{
	struct vxlan_net *vn;

	if (!vs)
		return false;
	if (!refcount_dec_and_test(&vs->refcnt))
		return false;

	vn = net_generic(sock_net(vs->sock->sk), vxlan_net_id);
	spin_lock(&vn->sock_lock);
	hlist_del_rcu(&vs->hlist);
	udp_tunnel_notify_del_rx_port(vs->sock,
				      (vs->flags & VXLAN_F_GPE) ?
				      UDP_TUNNEL_TYPE_VXLAN_GPE :
				      UDP_TUNNEL_TYPE_VXLAN);
	spin_unlock(&vn->sock_lock);

	return true;
}