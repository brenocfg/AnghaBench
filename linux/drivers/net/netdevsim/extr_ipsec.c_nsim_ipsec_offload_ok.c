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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct sk_buff {int dummy; } ;
struct nsim_ipsec {int /*<<< orphan*/  ok; } ;
struct netdevsim {struct nsim_ipsec ipsec; } ;

/* Variables and functions */
 struct netdevsim* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nsim_ipsec_offload_ok(struct sk_buff *skb, struct xfrm_state *xs)
{
	struct netdevsim *ns = netdev_priv(xs->xso.dev);
	struct nsim_ipsec *ipsec = &ns->ipsec;

	ipsec->ok++;

	return true;
}