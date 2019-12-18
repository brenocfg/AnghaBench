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
typedef  scalar_t__ u64 ;
struct sk_buff {int dummy; } ;
struct mlxsw_sp1_ptp_unmatched {scalar_t__ timestamp; struct sk_buff* skb; } ;
struct mlxsw_sp1_ptp_key {int /*<<< orphan*/  ingress; int /*<<< orphan*/  local_port; } ;
struct mlxsw_sp {TYPE_1__* ptp_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  unmatched_lock; } ;

/* Variables and functions */
 int E2BIG ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_packet_finish (struct mlxsw_sp*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_unmatched_finish (struct mlxsw_sp*,struct mlxsw_sp1_ptp_unmatched*) ; 
 struct mlxsw_sp1_ptp_unmatched* mlxsw_sp1_ptp_unmatched_lookup (struct mlxsw_sp*,struct mlxsw_sp1_ptp_key,int*) ; 
 int mlxsw_sp1_ptp_unmatched_remove (struct mlxsw_sp*,struct mlxsw_sp1_ptp_unmatched*) ; 
 int mlxsw_sp1_ptp_unmatched_save (struct mlxsw_sp*,struct mlxsw_sp1_ptp_key,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp1_ptp_got_piece(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp1_ptp_key key,
				    struct sk_buff *skb, u64 timestamp)
{
	struct mlxsw_sp1_ptp_unmatched *unmatched;
	int length;
	int err;

	rcu_read_lock();

	spin_lock(&mlxsw_sp->ptp_state->unmatched_lock);

	unmatched = mlxsw_sp1_ptp_unmatched_lookup(mlxsw_sp, key, &length);
	if (skb && unmatched && unmatched->timestamp) {
		unmatched->skb = skb;
	} else if (timestamp && unmatched && unmatched->skb) {
		unmatched->timestamp = timestamp;
	} else {
		/* Either there is no entry to match, or one that is there is
		 * incompatible.
		 */
		if (length < 100)
			err = mlxsw_sp1_ptp_unmatched_save(mlxsw_sp, key,
							   skb, timestamp);
		else
			err = -E2BIG;
		if (err && skb)
			mlxsw_sp1_ptp_packet_finish(mlxsw_sp, skb,
						    key.local_port,
						    key.ingress, NULL);
		unmatched = NULL;
	}

	if (unmatched) {
		err = mlxsw_sp1_ptp_unmatched_remove(mlxsw_sp, unmatched);
		WARN_ON_ONCE(err);
	}

	spin_unlock(&mlxsw_sp->ptp_state->unmatched_lock);

	if (unmatched)
		mlxsw_sp1_ptp_unmatched_finish(mlxsw_sp, unmatched);

	rcu_read_unlock();
}