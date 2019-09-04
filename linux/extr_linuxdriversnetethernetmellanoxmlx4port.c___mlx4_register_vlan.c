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
typedef  size_t u8 ;
typedef  int u16 ;
struct mlx4_vlan_table {scalar_t__ total; scalar_t__ max; int* refs; int* is_dup; int /*<<< orphan*/  mutex; void** entries; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* port; } ;
struct TYPE_3__ {struct mlx4_vlan_table vlan_table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int MLX4_MAX_VLAN_NUM ; 
 int MLX4_VLAN_MASK ; 
 int MLX4_VLAN_REGULAR ; 
 int MLX4_VLAN_VALID ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,...) ; 
 int mlx4_is_mf_bonded (struct mlx4_dev*) ; 
 int mlx4_need_mf_bond (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_set_port_vlan_table (struct mlx4_dev*,size_t,void**) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int __mlx4_register_vlan(struct mlx4_dev *dev, u8 port, u16 vlan,
				int *index)
{
	struct mlx4_vlan_table *table = &mlx4_priv(dev)->port[port].vlan_table;
	int i, err = 0;
	int free = -1;
	int free_for_dup = -1;
	bool dup = mlx4_is_mf_bonded(dev);
	u8 dup_port = (port == 1) ? 2 : 1;
	struct mlx4_vlan_table *dup_table = &mlx4_priv(dev)->port[dup_port].vlan_table;
	bool need_mf_bond = mlx4_need_mf_bond(dev);
	bool can_mf_bond = true;

	mlx4_dbg(dev, "Registering VLAN: %d for port %d %s duplicate\n",
		 vlan, port,
		 dup ? "with" : "without");

	if (need_mf_bond) {
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

	if (table->total == table->max) {
		/* No free vlan entries */
		err = -ENOSPC;
		goto out;
	}

	if (need_mf_bond) {
		int index_at_port = -1;
		int index_at_dup_port = -1;

		for (i = MLX4_VLAN_REGULAR; i < MLX4_MAX_VLAN_NUM; i++) {
			if (vlan == (MLX4_VLAN_MASK & be32_to_cpu(table->entries[i])))
				index_at_port = i;
			if (vlan == (MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[i])))
				index_at_dup_port = i;
		}
		/* check that same vlan is not in the tables at different indices */
		if ((index_at_port != index_at_dup_port) &&
		    (index_at_port >= 0) &&
		    (index_at_dup_port >= 0))
			can_mf_bond = false;

		/* If the vlan is already in the primary table, the slot must be
		 * available in the duplicate table as well.
		 */
		if (index_at_port >= 0 && index_at_dup_port < 0 &&
		    dup_table->refs[index_at_port]) {
			can_mf_bond = false;
		}
		/* If the vlan is already in the duplicate table, check that the
		 * corresponding index is not occupied in the primary table, or
		 * the primary table already contains the vlan at the same index.
		 * Otherwise, you cannot bond (primary contains a different vlan
		 * at that index).
		 */
		if (index_at_dup_port >= 0) {
			if (!table->refs[index_at_dup_port] ||
			    (vlan == (MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[index_at_dup_port]))))
				free_for_dup = index_at_dup_port;
			else
				can_mf_bond = false;
		}
	}

	for (i = MLX4_VLAN_REGULAR; i < MLX4_MAX_VLAN_NUM; i++) {
		if (!table->refs[i]) {
			if (free < 0)
				free = i;
			if (free_for_dup < 0 && need_mf_bond && can_mf_bond) {
				if (!dup_table->refs[i])
					free_for_dup = i;
			}
		}

		if ((table->refs[i] || table->is_dup[i]) &&
		    (vlan == (MLX4_VLAN_MASK &
			      be32_to_cpu(table->entries[i])))) {
			/* Vlan already registered, increase references count */
			mlx4_dbg(dev, "vlan %u is already registered.\n", vlan);
			*index = i;
			++table->refs[i];
			if (dup) {
				u16 dup_vlan = MLX4_VLAN_MASK & be32_to_cpu(dup_table->entries[i]);

				if (dup_vlan != vlan || !dup_table->is_dup[i]) {
					mlx4_warn(dev, "register vlan: expected duplicate vlan %u on port %d index %d\n",
						  vlan, dup_port, i);
				}
			}
			goto out;
		}
	}

	if (need_mf_bond && (free_for_dup < 0)) {
		if (dup) {
			mlx4_warn(dev, "Fail to allocate duplicate VLAN table entry\n");
			mlx4_warn(dev, "High Availability for virtual functions may not work as expected\n");
			dup = false;
		}
		can_mf_bond = false;
	}

	if (need_mf_bond && can_mf_bond)
		free = free_for_dup;

	if (free < 0) {
		err = -ENOMEM;
		goto out;
	}

	/* Register new VLAN */
	table->refs[free] = 1;
	table->is_dup[free] = false;
	table->entries[free] = cpu_to_be32(vlan | MLX4_VLAN_VALID);

	err = mlx4_set_port_vlan_table(dev, port, table->entries);
	if (unlikely(err)) {
		mlx4_warn(dev, "Failed adding vlan: %u\n", vlan);
		table->refs[free] = 0;
		table->entries[free] = 0;
		goto out;
	}
	++table->total;
	if (dup) {
		dup_table->refs[free] = 0;
		dup_table->is_dup[free] = true;
		dup_table->entries[free] = cpu_to_be32(vlan | MLX4_VLAN_VALID);

		err = mlx4_set_port_vlan_table(dev, dup_port, dup_table->entries);
		if (unlikely(err)) {
			mlx4_warn(dev, "Failed adding duplicate vlan: %u\n", vlan);
			dup_table->is_dup[free] = false;
			dup_table->entries[free] = 0;
			goto out;
		}
		++dup_table->total;
	}

	*index = free;
out:
	if (need_mf_bond) {
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