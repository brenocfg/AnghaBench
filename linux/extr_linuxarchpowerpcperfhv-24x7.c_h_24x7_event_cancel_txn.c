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
struct pmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_24x7_txn_flags ; 
 int /*<<< orphan*/  reset_txn () ; 

__attribute__((used)) static void h_24x7_event_cancel_txn(struct pmu *pmu)
{
	WARN_ON_ONCE(!__this_cpu_read(hv_24x7_txn_flags));
	reset_txn();
}