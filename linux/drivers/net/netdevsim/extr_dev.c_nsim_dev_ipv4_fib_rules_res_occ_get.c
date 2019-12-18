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
typedef  int /*<<< orphan*/  u64 ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSIM_RESOURCE_IPV4_FIB_RULES ; 
 int /*<<< orphan*/  nsim_fib_get_val (struct net*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 nsim_dev_ipv4_fib_rules_res_occ_get(void *priv)
{
	struct net *net = priv;

	return nsim_fib_get_val(net, NSIM_RESOURCE_IPV4_FIB_RULES, false);
}