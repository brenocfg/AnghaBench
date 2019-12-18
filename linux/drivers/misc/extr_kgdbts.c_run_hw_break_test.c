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
 int /*<<< orphan*/  hw_access_break_test ; 
 int /*<<< orphan*/  hw_break_val_access () ; 
 int /*<<< orphan*/  hw_break_val_write () ; 
 int /*<<< orphan*/  hw_write_break_test ; 
 scalar_t__ hwbreaks_ok ; 
 int /*<<< orphan*/  init_simple_test () ; 
 int /*<<< orphan*/  kgdb_breakpoint () ; 
 int test_complete ; 
 TYPE_1__ ts ; 

__attribute__((used)) static void run_hw_break_test(int is_write_test)
{
	test_complete = 0;
	init_simple_test();
	if (is_write_test) {
		ts.tst = hw_write_break_test;
		ts.name = "hw_write_break_test";
	} else {
		ts.tst = hw_access_break_test;
		ts.name = "hw_access_break_test";
	}
	/* Activate test with initial breakpoint */
	kgdb_breakpoint();
	hw_break_val_access();
	if (is_write_test) {
		if (test_complete == 2) {
			eprintk("kgdbts: ERROR %s broke on access\n",
				ts.name);
			hwbreaks_ok = 0;
		}
		hw_break_val_write();
	}
	kgdb_breakpoint();

	if (test_complete == 1)
		return;

	eprintk("kgdbts: ERROR %s test failed\n", ts.name);
	hwbreaks_ok = 0;
}