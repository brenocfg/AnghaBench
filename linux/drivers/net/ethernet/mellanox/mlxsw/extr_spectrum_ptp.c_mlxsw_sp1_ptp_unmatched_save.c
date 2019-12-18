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
struct sk_buff {int dummy; } ;
struct mlxsw_sp_ptp_state {int /*<<< orphan*/  unmatched_ht; scalar_t__ gc_cycle; } ;
struct mlxsw_sp1_ptp_key {int dummy; } ;
struct mlxsw_sp1_ptp_unmatched {int /*<<< orphan*/  ht_node; scalar_t__ gc_cycle; int /*<<< orphan*/  timestamp; struct sk_buff* skb; struct mlxsw_sp1_ptp_key key; } ;
struct mlxsw_sp {struct mlxsw_sp_ptp_state* ptp_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MLXSW_SP1_PTP_HT_GC_INTERVAL ; 
 int MLXSW_SP1_PTP_HT_GC_TIMEOUT ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp1_ptp_unmatched*) ; 
 struct mlxsw_sp1_ptp_unmatched* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp1_ptp_unmatched_ht_params ; 
 int rhltable_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp1_ptp_unmatched_save(struct mlxsw_sp *mlxsw_sp,
			     struct mlxsw_sp1_ptp_key key,
			     struct sk_buff *skb,
			     u64 timestamp)
{
	int cycles = MLXSW_SP1_PTP_HT_GC_TIMEOUT / MLXSW_SP1_PTP_HT_GC_INTERVAL;
	struct mlxsw_sp_ptp_state *ptp_state = mlxsw_sp->ptp_state;
	struct mlxsw_sp1_ptp_unmatched *unmatched;
	int err;

	unmatched = kzalloc(sizeof(*unmatched), GFP_ATOMIC);
	if (!unmatched)
		return -ENOMEM;

	unmatched->key = key;
	unmatched->skb = skb;
	unmatched->timestamp = timestamp;
	unmatched->gc_cycle = mlxsw_sp->ptp_state->gc_cycle + cycles;

	err = rhltable_insert(&ptp_state->unmatched_ht, &unmatched->ht_node,
			      mlxsw_sp1_ptp_unmatched_ht_params);
	if (err)
		kfree(unmatched);

	return err;
}