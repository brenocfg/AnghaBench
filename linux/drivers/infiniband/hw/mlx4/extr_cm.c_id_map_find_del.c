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
struct rb_root {int dummy; } ;
struct mlx4_ib_sriov {int /*<<< orphan*/  id_map_lock; int /*<<< orphan*/  pv_id_table; struct rb_root sl_id_map; } ;
struct id_map_entry {int /*<<< orphan*/  node; int /*<<< orphan*/  sl_cm_id; int /*<<< orphan*/  slave_id; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct mlx4_ib_sriov sriov; } ;

/* Variables and functions */
 struct id_map_entry* id_map_find_by_sl_id (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,struct rb_root*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 
 struct id_map_entry* xa_erase (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void id_map_find_del(struct ib_device *ibdev, int pv_cm_id)
{
	struct mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;
	struct rb_root *sl_id_map = &sriov->sl_id_map;
	struct id_map_entry *ent, *found_ent;

	spin_lock(&sriov->id_map_lock);
	ent = xa_erase(&sriov->pv_id_table, pv_cm_id);
	if (!ent)
		goto out;
	found_ent = id_map_find_by_sl_id(ibdev, ent->slave_id, ent->sl_cm_id);
	if (found_ent && found_ent == ent)
		rb_erase(&found_ent->node, sl_id_map);
out:
	spin_unlock(&sriov->id_map_lock);
}