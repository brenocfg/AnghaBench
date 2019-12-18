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
typedef  int u64 ;
struct res_common {int owner; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
 int ENOENT ; 
 int RES_QP ; 
 struct res_common* find_res (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mlx4_tlock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

int mlx4_get_slave_from_resource_id(struct mlx4_dev *dev,
				    enum mlx4_resource type,
				    u64 res_id, int *slave)
{

	struct res_common *r;
	int err = -ENOENT;
	int id = res_id;

	if (type == RES_QP)
		id &= 0x7fffff;
	spin_lock(mlx4_tlock(dev));

	r = find_res(dev, id, type);
	if (r) {
		*slave = r->owner;
		err = 0;
	}
	spin_unlock(mlx4_tlock(dev));

	return err;
}