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
struct mlx5_lag {int dummy; } ;
struct mlx5_fib_event_work {unsigned long event; struct mlx5_lag* ldev; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mlx5_fib_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_lag_fib_update ; 

__attribute__((used)) static struct mlx5_fib_event_work *
mlx5_lag_init_fib_work(struct mlx5_lag *ldev, unsigned long event)
{
	struct mlx5_fib_event_work *fib_work;

	fib_work = kzalloc(sizeof(*fib_work), GFP_ATOMIC);
	if (WARN_ON(!fib_work))
		return NULL;

	INIT_WORK(&fib_work->work, mlx5_lag_fib_update);
	fib_work->ldev = ldev;
	fib_work->event = event;

	return fib_work;
}