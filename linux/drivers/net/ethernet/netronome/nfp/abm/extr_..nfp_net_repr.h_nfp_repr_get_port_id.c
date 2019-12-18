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
struct nfp_repr {TYPE_3__* dst; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int port_id; } ;
struct TYPE_5__ {TYPE_1__ port_info; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 struct nfp_repr* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline int nfp_repr_get_port_id(struct net_device *netdev)
{
	struct nfp_repr *priv = netdev_priv(netdev);

	return priv->dst->u.port_info.port_id;
}