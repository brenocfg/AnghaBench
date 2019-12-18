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
typedef  int u64 ;
struct workqueue_struct {int dummy; } ;
struct TYPE_6__ {int use_emad; int /*<<< orphan*/  trans_list_lock; int /*<<< orphan*/  trans_list; int /*<<< orphan*/  tid; } ;
struct mlxsw_core {struct workqueue_struct* emad_wq; TYPE_3__ emad; TYPE_2__* driver; TYPE_1__* bus; } ;
struct TYPE_5__ {int (* basic_trap_groups_set ) (struct mlxsw_core*) ;} ;
struct TYPE_4__ {int features; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int MLXSW_BUS_F_TXRX ; 
 struct workqueue_struct* alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int mlxsw_core_trap_register (struct mlxsw_core*,int /*<<< orphan*/ *,struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_core_trap_unregister (struct mlxsw_core*,int /*<<< orphan*/ *,struct mlxsw_core*) ; 
 int /*<<< orphan*/  mlxsw_emad_rx_listener ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct mlxsw_core*) ; 

__attribute__((used)) static int mlxsw_emad_init(struct mlxsw_core *mlxsw_core)
{
	struct workqueue_struct *emad_wq;
	u64 tid;
	int err;

	if (!(mlxsw_core->bus->features & MLXSW_BUS_F_TXRX))
		return 0;

	emad_wq = alloc_workqueue("mlxsw_core_emad", 0, 0);
	if (!emad_wq)
		return -ENOMEM;
	mlxsw_core->emad_wq = emad_wq;

	/* Set the upper 32 bits of the transaction ID field to a random
	 * number. This allows us to discard EMADs addressed to other
	 * devices.
	 */
	get_random_bytes(&tid, 4);
	tid <<= 32;
	atomic64_set(&mlxsw_core->emad.tid, tid);

	INIT_LIST_HEAD(&mlxsw_core->emad.trans_list);
	spin_lock_init(&mlxsw_core->emad.trans_list_lock);

	err = mlxsw_core_trap_register(mlxsw_core, &mlxsw_emad_rx_listener,
				       mlxsw_core);
	if (err)
		return err;

	err = mlxsw_core->driver->basic_trap_groups_set(mlxsw_core);
	if (err)
		goto err_emad_trap_set;
	mlxsw_core->emad.use_emad = true;

	return 0;

err_emad_trap_set:
	mlxsw_core_trap_unregister(mlxsw_core, &mlxsw_emad_rx_listener,
				   mlxsw_core);
	destroy_workqueue(mlxsw_core->emad_wq);
	return err;
}