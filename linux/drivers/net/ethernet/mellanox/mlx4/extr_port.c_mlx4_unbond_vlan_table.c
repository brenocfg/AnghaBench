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
struct mlx4_vlan_table {scalar_t__* entries; int* is_dup; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * refs; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct mlx4_vlan_table vlan_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_MAX_VLAN_NUM ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_vlan_table (struct mlx4_dev*,int,scalar_t__*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx4_unbond_vlan_table(struct mlx4_dev *dev)
{
	struct mlx4_vlan_table *t1 = &mlx4_priv(dev)->port[1].vlan_table;
	struct mlx4_vlan_table *t2 = &mlx4_priv(dev)->port[2].vlan_table;
	int ret = 0;
	int ret1;
	int i;
	bool update1 = false;
	bool update2 = false;

	mutex_lock(&t1->mutex);
	mutex_lock(&t2->mutex);
	for (i = 0; i < MLX4_MAX_VLAN_NUM; i++) {
		if (t1->entries[i] != t2->entries[i]) {
			mlx4_warn(dev, "vlan table is in an unexpected state when trying to unbond\n");
			ret = -EINVAL;
			goto unlock;
		}
	}

	for (i = 0; i < MLX4_MAX_VLAN_NUM; i++) {
		if (!t1->entries[i])
			continue;
		t1->is_dup[i] = false;
		if (!t1->refs[i]) {
			t1->entries[i] = 0;
			update1 = true;
		}
		t2->is_dup[i] = false;
		if (!t2->refs[i]) {
			t2->entries[i] = 0;
			update2 = true;
		}
	}

	if (update1) {
		ret = mlx4_set_port_vlan_table(dev, 1, t1->entries);
		if (ret)
			mlx4_warn(dev, "failed to unmirror VLAN tables for port 1(%d)\n", ret);
	}
	if (update2) {
		ret1 = mlx4_set_port_vlan_table(dev, 2, t2->entries);
		if (ret1) {
			mlx4_warn(dev, "failed to unmirror VLAN tables for port 2(%d)\n", ret1);
			ret = ret1;
		}
	}
unlock:
	mutex_unlock(&t2->mutex);
	mutex_unlock(&t1->mutex);
	return ret;
}