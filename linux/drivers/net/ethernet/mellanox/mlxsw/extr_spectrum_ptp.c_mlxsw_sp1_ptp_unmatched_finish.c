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
struct TYPE_2__ {int /*<<< orphan*/  ingress; int /*<<< orphan*/  local_port; } ;
struct mlxsw_sp1_ptp_unmatched {TYPE_1__ key; scalar_t__ skb; scalar_t__ timestamp; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct mlxsw_sp1_ptp_unmatched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_packet_timestamp (struct mlxsw_sp*,TYPE_1__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_packet_finish (struct mlxsw_sp*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 

__attribute__((used)) static void
mlxsw_sp1_ptp_unmatched_finish(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp1_ptp_unmatched *unmatched)
{
	if (unmatched->skb && unmatched->timestamp)
		mlxsw_sp1_packet_timestamp(mlxsw_sp, unmatched->key,
					   unmatched->skb,
					   unmatched->timestamp);
	else if (unmatched->skb)
		mlxsw_sp1_ptp_packet_finish(mlxsw_sp, unmatched->skb,
					    unmatched->key.local_port,
					    unmatched->key.ingress, NULL);
	kfree_rcu(unmatched, rcu);
}