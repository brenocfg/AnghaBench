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
struct TYPE_4__ {scalar_t__ offload_handle; } ;
struct xfrm_state {TYPE_2__ xso; } ;
struct sk_buff {TYPE_1__* sp; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_features_t ;
struct TYPE_3__ {struct xfrm_state** xvec; scalar_t__ len; } ;

/* Variables and functions */

bool mlx5e_ipsec_feature_check(struct sk_buff *skb, struct net_device *netdev,
			       netdev_features_t features)
{
	struct xfrm_state *x;

	if (skb->sp && skb->sp->len) {
		x = skb->sp->xvec[0];
		if (x && x->xso.offload_handle)
			return true;
	}
	return false;
}