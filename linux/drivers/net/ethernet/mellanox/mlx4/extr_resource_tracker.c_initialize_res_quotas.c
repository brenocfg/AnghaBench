#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource_allocator {int* guaranteed; int* quota; int res_free; } ;
struct TYPE_4__ {scalar_t__ reserved_mtts; } ;
struct mlx4_dev {TYPE_2__ caps; TYPE_1__* persist; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;
struct TYPE_3__ {int num_vfs; } ;

/* Variables and functions */
 int RES_MTT ; 
 int mlx4_master_func_num (struct mlx4_dev*) ; 

__attribute__((used)) static inline void initialize_res_quotas(struct mlx4_dev *dev,
					 struct resource_allocator *res_alloc,
					 enum mlx4_resource res_type,
					 int vf, int num_instances)
{
	res_alloc->guaranteed[vf] = num_instances /
				    (2 * (dev->persist->num_vfs + 1));
	res_alloc->quota[vf] = (num_instances / 2) + res_alloc->guaranteed[vf];
	if (vf == mlx4_master_func_num(dev)) {
		res_alloc->res_free = num_instances;
		if (res_type == RES_MTT) {
			/* reserved mtts will be taken out of the PF allocation */
			res_alloc->res_free += dev->caps.reserved_mtts;
			res_alloc->guaranteed[vf] += dev->caps.reserved_mtts;
			res_alloc->quota[vf] += dev->caps.reserved_mtts;
		}
	}
}