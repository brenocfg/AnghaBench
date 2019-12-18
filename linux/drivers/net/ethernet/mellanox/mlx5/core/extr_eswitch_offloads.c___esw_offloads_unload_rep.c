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
struct mlx5_eswitch {TYPE_3__ offloads; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* unload ) (struct mlx5_eswitch_rep*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ REP_LOADED ; 
 int /*<<< orphan*/  REP_REGISTERED ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_eswitch_rep*) ; 

__attribute__((used)) static void __esw_offloads_unload_rep(struct mlx5_eswitch *esw,
				      struct mlx5_eswitch_rep *rep, u8 rep_type)
{
	if (atomic_cmpxchg(&rep->rep_data[rep_type].state,
			   REP_LOADED, REP_REGISTERED) == REP_LOADED)
		esw->offloads.rep_ops[rep_type]->unload(rep);
}