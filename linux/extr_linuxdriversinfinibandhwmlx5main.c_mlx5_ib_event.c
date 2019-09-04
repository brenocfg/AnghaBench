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
struct mlx5_ib_event_work {unsigned long param; int event; int /*<<< orphan*/  work; void* context; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_event_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_event_wq ; 
 int /*<<< orphan*/  mlx5_ib_handle_event ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_event(struct mlx5_core_dev *dev, void *context,
			  enum mlx5_dev_event event, unsigned long param)
{
	struct mlx5_ib_event_work *work;

	work = kmalloc(sizeof(*work), GFP_ATOMIC);
	if (!work)
		return;

	INIT_WORK(&work->work, mlx5_ib_handle_event);
	work->dev = dev;
	work->param = param;
	work->context = context;
	work->event = event;

	queue_work(mlx5_ib_event_wq, &work->work);
}