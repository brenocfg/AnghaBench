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
typedef  unsigned long long u64 ;
struct TYPE_2__ {int flags; int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 unsigned long long MLX4_ASYNC_EVENT_MASK ; 
 int MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT ; 
 int MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV ; 
 unsigned long long MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT ; 
 unsigned long long MLX4_EVENT_TYPE_RECOVERABLE_ERROR_EVENT ; 

__attribute__((used)) static u64 get_async_ev_mask(struct mlx4_dev *dev)
{
	u64 async_ev_mask = MLX4_ASYNC_EVENT_MASK;
	if (dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV)
		async_ev_mask |= (1ull << MLX4_EVENT_TYPE_PORT_MNG_CHG_EVENT);
	if (dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_RECOVERABLE_ERROR_EVENT)
		async_ev_mask |= (1ull << MLX4_EVENT_TYPE_RECOVERABLE_ERROR_EVENT);

	return async_ev_mask;
}