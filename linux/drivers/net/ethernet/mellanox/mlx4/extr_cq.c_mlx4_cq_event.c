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
typedef  int u32 ;
struct TYPE_3__ {int num_cqs; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cq_table {int /*<<< orphan*/  tree; } ;
struct mlx4_cq {int /*<<< orphan*/  (* event ) (struct mlx4_cq*,int) ;} ;
struct TYPE_4__ {struct mlx4_cq_table cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 
 struct mlx4_cq* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct mlx4_cq*,int) ; 

void mlx4_cq_event(struct mlx4_dev *dev, u32 cqn, int event_type)
{
	struct mlx4_cq_table *cq_table = &mlx4_priv(dev)->cq_table;
	struct mlx4_cq *cq;

	rcu_read_lock();
	cq = radix_tree_lookup(&cq_table->tree, cqn & (dev->caps.num_cqs - 1));
	rcu_read_unlock();

	if (!cq) {
		mlx4_dbg(dev, "Async event for bogus CQ %08x\n", cqn);
		return;
	}

	/* Acessing the CQ outside of rcu_read_lock is safe, because
	 * the CQ is freed only after interrupt handling is completed.
	 */
	cq->event(cq, event_type);
}