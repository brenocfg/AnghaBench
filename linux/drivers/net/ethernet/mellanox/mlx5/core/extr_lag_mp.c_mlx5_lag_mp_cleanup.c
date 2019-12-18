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
 int /*<<< orphan*/  unregister_fib_notifier (TYPE_1__*) ; 

void mlx5_lag_mp_cleanup(struct mlx5_lag *ldev)
{
	struct lag_mp *mp = &ldev->lag_mp;

	if (!mp->fib_nb.notifier_call)
		return;

	unregister_fib_notifier(&mp->fib_nb);
	mp->fib_nb.notifier_call = NULL;
}