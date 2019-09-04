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
struct timer_list {int dummy; } ;
struct mlx5_ib_dev {scalar_t__ fill_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  delay_timer ; 
 struct mlx5_ib_dev* dev ; 
 struct mlx5_ib_dev* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delay_time_func(struct timer_list *t)
{
	struct mlx5_ib_dev *dev = from_timer(dev, t, delay_timer);

	dev->fill_delay = 0;
}