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
 int /*<<< orphan*/  eprintk (char*,char*) ; 
 int /*<<< orphan*/  hw_breakpoint_test ; 
 scalar_t__ hwbreaks_ok ; 
 int /*<<< orphan*/  init_simple_test () ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 
 int /*<<< orphan*/  kgdbts_break_test () ; 
 int /*<<< orphan*/  sw_breakpoint_test ; 
 scalar_t__ test_complete ; 
 TYPE_1__ ts ; 

__attribute__((used)) static void run_breakpoint_test(int is_hw_breakpoint)
{
	test_complete = 0;
	init_simple_test();
	if (is_hw_breakpoint) {
		ts.tst = hw_breakpoint_test;
		ts.name = "hw_breakpoint_test";
	} else {
		ts.tst = sw_breakpoint_test;
		ts.name = "sw_breakpoint_test";
	}
	/* Activate test with initial breakpoint */
	kgdb_breakpoint();
	/* run code with the break point in it */
	kgdbts_break_test();
	kgdb_breakpoint();

	if (test_complete)
		return;

	eprintk("kgdbts: ERROR %s test failed\n", ts.name);
	if (is_hw_breakpoint)
		hwbreaks_ok = 0;
}