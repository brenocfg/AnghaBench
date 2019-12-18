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
struct net_device {int dummy; } ;
struct cnic_ops {int /*<<< orphan*/  (* cnic_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct bnx2x {int /*<<< orphan*/  cnic_data; int /*<<< orphan*/  cnic_ops; int /*<<< orphan*/  panic; int /*<<< orphan*/  igu_dsb_id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CNIC_LOADED (struct bnx2x*) ; 
 int /*<<< orphan*/  IGU_INT_DISABLE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  USTORM_ID ; 
 int /*<<< orphan*/  bnx2x_ack_sb (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_task (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 struct cnic_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

irqreturn_t bnx2x_msix_sp_int(int irq, void *dev_instance)
{
	struct net_device *dev = dev_instance;
	struct bnx2x *bp = netdev_priv(dev);

	bnx2x_ack_sb(bp, bp->igu_dsb_id, USTORM_ID, 0,
		     IGU_INT_DISABLE, 0);

#ifdef BNX2X_STOP_ON_ERROR
	if (unlikely(bp->panic))
		return IRQ_HANDLED;
#endif

	if (CNIC_LOADED(bp)) {
		struct cnic_ops *c_ops;

		rcu_read_lock();
		c_ops = rcu_dereference(bp->cnic_ops);
		if (c_ops)
			c_ops->cnic_handler(bp->cnic_data, NULL);
		rcu_read_unlock();
	}

	/* schedule sp task to perform default status block work, ack
	 * attentions and enable interrupts.
	 */
	bnx2x_schedule_sp_task(bp);

	return IRQ_HANDLED;
}