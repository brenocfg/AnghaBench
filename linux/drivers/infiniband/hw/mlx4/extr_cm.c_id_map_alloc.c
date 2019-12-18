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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_ib_sriov {int /*<<< orphan*/  id_map_lock; int /*<<< orphan*/  cm_list; int /*<<< orphan*/  pv_id_next; int /*<<< orphan*/  pv_id_table; } ;
struct id_map_entry {int slave_id; int /*<<< orphan*/  list; int /*<<< orphan*/  pv_cm_id; int /*<<< orphan*/  timeout; TYPE_1__* dev; scalar_t__ scheduled_delete; int /*<<< orphan*/  sl_cm_id; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct mlx4_ib_sriov sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct id_map_entry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  id_map_ent_timeout ; 
 int /*<<< orphan*/  kfree (struct id_map_entry*) ; 
 struct id_map_entry* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_ib_warn (struct ib_device*,char*,int) ; 
 int /*<<< orphan*/  sl_id_map_add (struct ib_device*,struct id_map_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (struct ib_device*) ; 
 int xa_alloc_cyclic (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct id_map_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 

__attribute__((used)) static struct id_map_entry *
id_map_alloc(struct ib_device *ibdev, int slave_id, u32 sl_cm_id)
{
	int ret;
	struct id_map_entry *ent;
	struct mlx4_ib_sriov *sriov = &to_mdev(ibdev)->sriov;

	ent = kmalloc(sizeof (struct id_map_entry), GFP_KERNEL);
	if (!ent)
		return ERR_PTR(-ENOMEM);

	ent->sl_cm_id = sl_cm_id;
	ent->slave_id = slave_id;
	ent->scheduled_delete = 0;
	ent->dev = to_mdev(ibdev);
	INIT_DELAYED_WORK(&ent->timeout, id_map_ent_timeout);

	ret = xa_alloc_cyclic(&sriov->pv_id_table, &ent->pv_cm_id, ent,
			xa_limit_32b, &sriov->pv_id_next, GFP_KERNEL);
	if (ret >= 0) {
		spin_lock(&sriov->id_map_lock);
		sl_id_map_add(ibdev, ent);
		list_add_tail(&ent->list, &sriov->cm_list);
		spin_unlock(&sriov->id_map_lock);
		return ent;
	}

	/*error flow*/
	kfree(ent);
	mlx4_ib_warn(ibdev, "Allocation failed (err:0x%x)\n", ret);
	return ERR_PTR(-ENOMEM);
}