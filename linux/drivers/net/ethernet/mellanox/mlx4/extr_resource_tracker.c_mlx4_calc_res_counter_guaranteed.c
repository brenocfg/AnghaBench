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
struct resource_allocator {int res_reserved; } ;
struct TYPE_2__ {int num_ports; int max_counters; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_active_ports {int /*<<< orphan*/  ports; } ;

/* Variables and functions */
 int MLX4_PF_COUNTERS_PER_PORT ; 
 int MLX4_VF_COUNTERS_PER_PORT ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 struct mlx4_active_ports mlx4_get_active_ports (struct mlx4_dev*,int) ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 

__attribute__((used)) static int
mlx4_calc_res_counter_guaranteed(struct mlx4_dev *dev,
				 struct resource_allocator *res_alloc,
				 int vf)
{
	struct mlx4_active_ports actv_ports;
	int ports, counters_guaranteed;

	/* For master, only allocate according to the number of phys ports */
	if (vf == mlx4_master_func_num(dev))
		return MLX4_PF_COUNTERS_PER_PORT * dev->caps.num_ports;

	/* calculate real number of ports for the VF */
	actv_ports = mlx4_get_active_ports(dev, vf);
	ports = bitmap_weight(actv_ports.ports, dev->caps.num_ports);
	counters_guaranteed = ports * MLX4_VF_COUNTERS_PER_PORT;

	/* If we do not have enough counters for this VF, do not
	 * allocate any for it. '-1' to reduce the sink counter.
	 */
	if ((res_alloc->res_reserved + counters_guaranteed) >
	    (dev->caps.max_counters - 1))
		return 0;

	return counters_guaranteed;
}