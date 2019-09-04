#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ qpn; } ;
struct mlx4_ib_qp {TYPE_1__ mqp; } ;
struct mlx4_ib_dev {TYPE_3__* dev; } ;
struct TYPE_5__ {scalar_t__ base_tunnel_sqpn; } ;
struct TYPE_6__ {TYPE_2__ phys_caps; } ;

/* Variables and functions */
 int MLX4_MFUNC_MAX ; 
 int /*<<< orphan*/  mlx4_is_master (TYPE_3__*) ; 

__attribute__((used)) static int is_tunnel_qp(struct mlx4_ib_dev *dev, struct mlx4_ib_qp *qp)
{
	if (!mlx4_is_master(dev->dev))
		return 0;

	return qp->mqp.qpn >= dev->dev->phys_caps.base_tunnel_sqpn &&
	       qp->mqp.qpn < dev->dev->phys_caps.base_tunnel_sqpn +
		8 * MLX4_MFUNC_MAX;
}