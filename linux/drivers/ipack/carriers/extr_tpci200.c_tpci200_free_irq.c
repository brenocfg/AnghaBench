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
struct tpci200_board {int /*<<< orphan*/  mutex; TYPE_1__* slots; } ;
struct slot_irq {int dummy; } ;
struct ipack_device {size_t slot; } ;
struct TYPE_2__ {struct slot_irq* irq; } ;

/* Variables and functions */
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (struct slot_irq*,int /*<<< orphan*/ *) ; 
 struct tpci200_board* check_slot (struct ipack_device*) ; 
 int /*<<< orphan*/  kfree (struct slot_irq*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  tpci200_disable_irq (struct tpci200_board*,size_t) ; 

__attribute__((used)) static int tpci200_free_irq(struct ipack_device *dev)
{
	struct slot_irq *slot_irq;
	struct tpci200_board *tpci200;

	tpci200 = check_slot(dev);
	if (tpci200 == NULL)
		return -EINVAL;

	if (mutex_lock_interruptible(&tpci200->mutex))
		return -ERESTARTSYS;

	if (tpci200->slots[dev->slot].irq == NULL) {
		mutex_unlock(&tpci200->mutex);
		return -EINVAL;
	}

	tpci200_disable_irq(tpci200, dev->slot);
	slot_irq = tpci200->slots[dev->slot].irq;
	/* uninstall handler */
	RCU_INIT_POINTER(tpci200->slots[dev->slot].irq, NULL);
	synchronize_rcu();
	kfree(slot_irq);
	mutex_unlock(&tpci200->mutex);
	return 0;
}