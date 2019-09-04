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
struct kcs_bmc {int running; int /*<<< orphan*/  lock; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct kcs_bmc* to_kcs_bmc (struct file*) ; 

__attribute__((used)) static int kcs_bmc_open(struct inode *inode, struct file *filp)
{
	struct kcs_bmc *kcs_bmc = to_kcs_bmc(filp);
	int ret = 0;

	spin_lock_irq(&kcs_bmc->lock);
	if (!kcs_bmc->running)
		kcs_bmc->running = 1;
	else
		ret = -EBUSY;
	spin_unlock_irq(&kcs_bmc->lock);

	return ret;
}