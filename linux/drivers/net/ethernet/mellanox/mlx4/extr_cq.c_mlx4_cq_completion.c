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
typedef  int u32 ;
struct TYPE_5__ {int num_cqs; } ;
struct mlx4_dev {TYPE_2__ caps; } ;
struct mlx4_cq {int /*<<< orphan*/  (* comp ) (struct mlx4_cq*) ;int /*<<< orphan*/  arm_sn; } ;
struct TYPE_4__ {int /*<<< orphan*/  tree; } ;
struct TYPE_6__ {TYPE_1__ cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int) ; 
 TYPE_3__* mlx4_priv (struct mlx4_dev*) ; 
 struct mlx4_cq* radix_tree_lookup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (struct mlx4_cq*) ; 

void mlx4_cq_completion(struct mlx4_dev *dev, u32 cqn)
{
	struct mlx4_cq *cq;

	rcu_read_lock();
	cq = radix_tree_lookup(&mlx4_priv(dev)->cq_table.tree,
			       cqn & (dev->caps.num_cqs - 1));
	rcu_read_unlock();

	if (!cq) {
		mlx4_dbg(dev, "Completion event for bogus CQ %08x\n", cqn);
		return;
	}

	/* Acessing the CQ outside of rcu_read_lock is safe, because
	 * the CQ is freed only after interrupt handling is completed.
	 */
	++cq->arm_sn;

	cq->comp(cq);
}