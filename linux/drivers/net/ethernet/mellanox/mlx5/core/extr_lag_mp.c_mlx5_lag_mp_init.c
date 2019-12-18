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
struct TYPE_2__ {int /*<<< orphan*/ * notifier_call; } ;
struct lag_mp {TYPE_1__ fib_nb; } ;
struct mlx5_lag {struct lag_mp lag_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mlx5_lag_fib_event ; 
 int /*<<< orphan*/  mlx5_lag_fib_event_flush ; 
 int register_fib_notifier (TYPE_1__*,int /*<<< orphan*/ ) ; 

int mlx5_lag_mp_init(struct mlx5_lag *ldev)
{
	struct lag_mp *mp = &ldev->lag_mp;
	int err;

	if (mp->fib_nb.notifier_call)
		return 0;

	mp->fib_nb.notifier_call = mlx5_lag_fib_event;
	err = register_fib_notifier(&mp->fib_nb,
				    mlx5_lag_fib_event_flush);
	if (err)
		mp->fib_nb.notifier_call = NULL;

	return err;
}