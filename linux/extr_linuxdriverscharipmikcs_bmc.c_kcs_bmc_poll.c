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
struct kcs_bmc {int /*<<< orphan*/  lock; scalar_t__ data_in_avail; int /*<<< orphan*/  queue; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct kcs_bmc* to_kcs_bmc (struct file*) ; 

__attribute__((used)) static __poll_t kcs_bmc_poll(struct file *filp, poll_table *wait)
{
	struct kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	__poll_t mask = 0;

	poll_wait(filp, &kcs_bmc->queue, wait);

	spin_lock_irq(&kcs_bmc->lock);
	if (kcs_bmc->data_in_avail)
		mask |= EPOLLIN;
	spin_unlock_irq(&kcs_bmc->lock);

	return mask;
}