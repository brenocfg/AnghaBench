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
typedef  scalar_t__ u32 ;
struct mlx4_ib_dev {scalar_t__ steering_support; scalar_t__ steer_qpn_base; int /*<<< orphan*/  ib_uc_qpns_bitmap; } ;

/* Variables and functions */
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 scalar_t__ WARN (int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_release_region (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_count_order (int) ; 

void mlx4_ib_steer_qp_free(struct mlx4_ib_dev *dev, u32 qpn, int count)
{
	if (!qpn ||
	    dev->steering_support != MLX4_STEERING_MODE_DEVICE_MANAGED)
		return;

	if (WARN(qpn < dev->steer_qpn_base, "qpn = %u, steer_qpn_base = %u\n",
		 qpn, dev->steer_qpn_base))
		/* not supposed to be here */
		return;

	bitmap_release_region(dev->ib_uc_qpns_bitmap,
			      qpn - dev->steer_qpn_base,
			      get_count_order(count));
}