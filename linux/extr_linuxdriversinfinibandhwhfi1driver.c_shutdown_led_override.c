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
struct hfi1_pportdata {int /*<<< orphan*/  led_override_timer_active; int /*<<< orphan*/  led_override_timer; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCC_CFG_LED_CNTRL ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void shutdown_led_override(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;

	/*
	 * This pairs with the memory barrier in hfi1_start_led_override to
	 * ensure that we read the correct state of LED beaconing represented
	 * by led_override_timer_active
	 */
	smp_rmb();
	if (atomic_read(&ppd->led_override_timer_active)) {
		del_timer_sync(&ppd->led_override_timer);
		atomic_set(&ppd->led_override_timer_active, 0);
		/* Ensure the atomic_set is visible to all CPUs */
		smp_wmb();
	}

	/* Hand control of the LED to the DC for normal operation */
	write_csr(dd, DCC_CFG_LED_CNTRL, 0);
}