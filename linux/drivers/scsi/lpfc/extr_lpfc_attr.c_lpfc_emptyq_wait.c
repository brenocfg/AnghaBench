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
struct lpfc_hba {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_emptyq_wait(struct lpfc_hba *phba, struct list_head *q, spinlock_t *lock)
{
	int cnt = 0;

	spin_lock_irq(lock);
	while (!list_empty(q)) {
		spin_unlock_irq(lock);
		msleep(20);
		if (cnt++ > 250) {  /* 5 secs */
			lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
					"0466 %s %s\n",
					"Outstanding IO when ",
					"bringing Adapter offline\n");
				return 0;
		}
		spin_lock_irq(lock);
	}
	spin_unlock_irq(lock);
	return 1;
}