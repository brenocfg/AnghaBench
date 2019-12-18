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
struct mlx5_core_dev {int dummy; } ;
typedef  int __be64 ;

/* Variables and functions */
 int* MLX5_CAP_DEV_EVENT (struct mlx5_core_dev*,int*) ; 
 int /*<<< orphan*/  be64_to_cpu (int) ; 

__attribute__((used)) static void gather_user_async_events(struct mlx5_core_dev *dev, u64 mask[4])
{
	__be64 *user_unaffiliated_events;
	__be64 *user_affiliated_events;
	int i;

	user_affiliated_events =
		MLX5_CAP_DEV_EVENT(dev, user_affiliated_events);
	user_unaffiliated_events =
		MLX5_CAP_DEV_EVENT(dev, user_unaffiliated_events);

	for (i = 0; i < 4; i++)
		mask[i] |= be64_to_cpu(user_affiliated_events[i] |
				       user_unaffiliated_events[i]);
}