#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct timer_list {int dummy; } ;
struct mlx5_core_health {scalar_t__ prev; scalar_t__ miss_counter; int sick; int /*<<< orphan*/  timer; int /*<<< orphan*/  health_counter; } ;
struct TYPE_6__ {struct mlx5_core_health health; } ;
struct mlx5_core_dev {scalar_t__ state; TYPE_3__* pdev; TYPE_2__ priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  timer; } ;
struct TYPE_8__ {TYPE_1__ health; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MAX_MISSES ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 struct mlx5_core_dev* dev ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mlx5_core_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_next_poll_jiffies () ; 
 scalar_t__ in_fatal (struct mlx5_core_dev*) ; 
 scalar_t__ ioread32be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_trigger_health_work (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_health_info (struct mlx5_core_dev*) ; 
 TYPE_4__ priv ; 

__attribute__((used)) static void poll_health(struct timer_list *t)
{
	struct mlx5_core_dev *dev = from_timer(dev, t, priv.health.timer);
	struct mlx5_core_health *health = &dev->priv.health;
	u32 count;

	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR)
		goto out;

	count = ioread32be(health->health_counter);
	if (count == health->prev)
		++health->miss_counter;
	else
		health->miss_counter = 0;

	health->prev = count;
	if (health->miss_counter == MAX_MISSES) {
		dev_err(&dev->pdev->dev, "device's health compromised - reached miss count\n");
		print_health_info(dev);
	}

	if (in_fatal(dev) && !health->sick) {
		health->sick = true;
		print_health_info(dev);
		mlx5_trigger_health_work(dev);
	}

out:
	mod_timer(&health->timer, get_next_poll_jiffies());
}