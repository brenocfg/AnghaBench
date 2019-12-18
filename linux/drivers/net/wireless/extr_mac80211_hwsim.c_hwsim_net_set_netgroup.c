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
struct net {int dummy; } ;
struct hwsim_net {scalar_t__ netgroup; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hwsim_net_id ; 
 int /*<<< orphan*/  hwsim_netgroup_ida ; 
 scalar_t__ ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hwsim_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hwsim_net_set_netgroup(struct net *net)
{
	struct hwsim_net *hwsim_net = net_generic(net, hwsim_net_id);

	hwsim_net->netgroup = ida_simple_get(&hwsim_netgroup_ida,
					     0, 0, GFP_KERNEL);
	return hwsim_net->netgroup >= 0 ? 0 : -ENOMEM;
}