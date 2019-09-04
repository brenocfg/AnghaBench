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
struct mlx5_priv {int /*<<< orphan*/  waiting_events_list; } ;
struct mlx5_delayed_event {int event; unsigned long param; int /*<<< orphan*/  list; struct mlx5_core_dev* dev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_dev_event { ____Placeholder_mlx5_dev_event } mlx5_dev_event ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct mlx5_delayed_event* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int) ; 

__attribute__((used)) static void add_delayed_event(struct mlx5_priv *priv,
			      struct mlx5_core_dev *dev,
			      enum mlx5_dev_event event,
			      unsigned long param)
{
	struct mlx5_delayed_event *delayed_event;

	delayed_event = kzalloc(sizeof(*delayed_event), GFP_ATOMIC);
	if (!delayed_event) {
		mlx5_core_err(dev, "event %d is missed\n", event);
		return;
	}

	mlx5_core_dbg(dev, "Accumulating event %d\n", event);
	delayed_event->dev = dev;
	delayed_event->event = event;
	delayed_event->param = param;
	list_add_tail(&delayed_event->list, &priv->waiting_events_list);
}