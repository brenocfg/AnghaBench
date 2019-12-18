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
typedef  size_t u8 ;
struct mlx5_eswitch_rep {TYPE_1__* rep_data; } ;
struct TYPE_6__ {TYPE_2__** rep_ops; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; TYPE_3__ offloads; } ;
struct TYPE_5__ {int (* load ) (int /*<<< orphan*/ ,struct mlx5_eswitch_rep*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  REP_LOADED ; 
 scalar_t__ REP_REGISTERED ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,struct mlx5_eswitch_rep*) ; 

__attribute__((used)) static int __esw_offloads_load_rep(struct mlx5_eswitch *esw,
				   struct mlx5_eswitch_rep *rep, u8 rep_type)
{
	int err = 0;

	if (atomic_cmpxchg(&rep->rep_data[rep_type].state,
			   REP_REGISTERED, REP_LOADED) == REP_REGISTERED) {
		err = esw->offloads.rep_ops[rep_type]->load(esw->dev, rep);
		if (err)
			atomic_set(&rep->rep_data[rep_type].state,
				   REP_REGISTERED);
	}

	return err;
}