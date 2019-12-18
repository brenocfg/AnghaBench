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
struct mlxsw_sp1_ptp_unmatched {scalar_t__ skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  kfree_rcu (struct mlxsw_sp1_ptp_unmatched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void mlxsw_sp1_ptp_unmatched_free_fn(void *ptr, void *arg)
{
	struct mlxsw_sp1_ptp_unmatched *unmatched = ptr;

	/* This is invoked at a point where the ports are gone already. Nothing
	 * to do with whatever is left in the HT but to free it.
	 */
	if (unmatched->skb)
		dev_kfree_skb_any(unmatched->skb);
	kfree_rcu(unmatched, rcu);
}