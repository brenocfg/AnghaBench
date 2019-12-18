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
struct atl1_adapter {int /*<<< orphan*/  int_enabled; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMR_NORXTX_MASK ; 
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atlx_imr_set (struct atl1_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule_prep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int atl1_sched_rings_clean(struct atl1_adapter* adapter)
{
	if (!napi_schedule_prep(&adapter->napi))
		/* It is possible in case even the RX/TX ints are disabled via IMR
		 * register the ISR bits are set anyway (but do not produce IRQ).
		 * To handle such situation the napi functions used to check is
		 * something scheduled or not.
		 */
		return 0;

	__napi_schedule(&adapter->napi);

	/*
	 * Disable RX/TX ints via IMR register if it is
	 * allowed. NAPI handler must reenable them in same
	 * way.
	 */
	if (!adapter->int_enabled)
		return 1;

	atlx_imr_set(adapter, IMR_NORXTX_MASK);
	return 1;
}