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

/* Variables and functions */
 int /*<<< orphan*/  ipvlan_net_ops ; 
 int register_pernet_subsys (int /*<<< orphan*/ *) ; 

int ipvlan_l3s_init(void)
{
	return register_pernet_subsys(&ipvlan_net_ops);
}