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
struct hfi1_devdata {int /*<<< orphan*/ * kernel_send_context; int /*<<< orphan*/  pio_map_lock; int /*<<< orphan*/  pio_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pio_map_free (scalar_t__) ; 
 scalar_t__ rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void free_pio_map(struct hfi1_devdata *dd)
{
	/* Free PIO map if allocated */
	if (rcu_access_pointer(dd->pio_map)) {
		spin_lock_irq(&dd->pio_map_lock);
		pio_map_free(rcu_access_pointer(dd->pio_map));
		RCU_INIT_POINTER(dd->pio_map, NULL);
		spin_unlock_irq(&dd->pio_map_lock);
		synchronize_rcu();
	}
	kfree(dd->kernel_send_context);
	dd->kernel_send_context = NULL;
}