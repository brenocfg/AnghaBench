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
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {int dummy; } ;
struct mlxsw_sp1_ptp_key {int /*<<< orphan*/  ingress; int /*<<< orphan*/  local_port; } ;
struct mlxsw_sp {TYPE_1__* clock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp1_ptp_packet_finish (struct mlxsw_sp*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timecounter_cyc2time (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp1_packet_timestamp(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp1_ptp_key key,
				       struct sk_buff *skb,
				       u64 timestamp)
{
	struct skb_shared_hwtstamps hwtstamps;
	u64 nsec;

	spin_lock_bh(&mlxsw_sp->clock->lock);
	nsec = timecounter_cyc2time(&mlxsw_sp->clock->tc, timestamp);
	spin_unlock_bh(&mlxsw_sp->clock->lock);

	hwtstamps.hwtstamp = ns_to_ktime(nsec);
	mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb,
				    key.local_port, key.ingress, &hwtstamps);
}