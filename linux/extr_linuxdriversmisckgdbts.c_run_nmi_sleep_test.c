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
struct TYPE_2__ {char* name; int /*<<< orphan*/  tst; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintk (char*,...) ; 
 int /*<<< orphan*/  init_simple_test () ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  nmi_sleep_test ; 
 int test_complete ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 TYPE_1__ ts ; 

__attribute__((used)) static void run_nmi_sleep_test(int nmi_sleep)
{
	unsigned long flags;

	init_simple_test();
	ts.tst = nmi_sleep_test;
	ts.name = "nmi_sleep_test";
	/* Activate test with initial breakpoint */
	kgdb_breakpoint();
	local_irq_save(flags);
	mdelay(nmi_sleep*1000);
	touch_nmi_watchdog();
	local_irq_restore(flags);
	if (test_complete != 2)
		eprintk("kgdbts: ERROR nmi_test did not hit nmi\n");
	kgdb_breakpoint();
	if (test_complete == 1)
		return;

	eprintk("kgdbts: ERROR %s test failed\n", ts.name);
}