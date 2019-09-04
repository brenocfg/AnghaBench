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
typedef  size_t u8 ;
typedef  int u64 ;
struct mlx4_mac_table {int /*<<< orphan*/  mutex; void** entries; } ;
struct mlx4_port_info {int base_qpn; struct mlx4_mac_table mac_table; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_2__ {struct mlx4_port_info* port; } ;

/* Variables and functions */
 int MLX4_MAC_VALID ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 void* cpu_to_be64 (int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,unsigned long long) ; 
 int mlx4_is_mf_bonded (struct mlx4_dev*) ; 
 TYPE_1__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_mac_table (struct mlx4_dev*,size_t,void**) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int validate_index (struct mlx4_dev*,struct mlx4_mac_table*,int) ; 

int __mlx4_replace_mac(struct mlx4_dev *dev, u8 port, int qpn, u64 new_mac)
{
	struct mlx4_port_info *info = &mlx4_priv(dev)->port[port];
	struct mlx4_mac_table *table = &info->mac_table;
	int index = qpn - info->base_qpn;
	int err = 0;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	struct mlx4_mac_table *dup_table = &mlx4_priv(dev)->port[dup_port].mac_table;

	/* CX1 doesn't support multi-functions */
	if (dup) {
		if (port == 1) {
			mutex_lock(&table->mutex);
			mutex_lock_nested(&dup_table->mutex, SINGLE_DEPTH_NESTING);
		} else {
			mutex_lock(&dup_table->mutex);
			mutex_lock_nested(&table->mutex, SINGLE_DEPTH_NESTING);
		}
	} else {
		mutex_lock(&table->mutex);
	}

	err = validate_index(dev, table, index);
	if (err)
		goto out;

	table->entries[index] = cpu_to_be64(new_mac | MLX4_MAC_VALID);

	err = mlx4_set_port_mac_table(dev, port, table->entries);
	if (unlikely(err)) {
		mlx4_err(dev, "Failed adding MAC: 0x%llx\n",
			 (unsigned long long) new_mac);
		table->entries[index] = 0;
	} else {
		if (dup) {
			dup_table->entries[index] = cpu_to_be64(new_mac | MLX4_MAC_VALID);

			err = mlx4_set_port_mac_table(dev, dup_port, dup_table->entries);
			if (unlikely(err)) {
				mlx4_err(dev, "Failed adding duplicate MAC: 0x%llx\n",
					 (unsigned long long)new_mac);
				dup_table->entries[index] = 0;
			}
		}
	}
out:
	if (dup) {
		if (port == 2) {
			mutex_unlock(&table->mutex);
			mutex_unlock(&dup_table->mutex);
		} else {
			mutex_unlock(&dup_table->mutex);
			mutex_unlock(&table->mutex);
		}
	} else {
		mutex_unlock(&table->mutex);
	}
	return err;
}