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

/* Variables and functions */
 int /*<<< orphan*/  test_after2_probe ; 
 int /*<<< orphan*/  test_after_probe ; 
 int /*<<< orphan*/  test_before_probe ; 
 int /*<<< orphan*/  test_case_probe ; 
 int /*<<< orphan*/  unregister_test_probe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_case_cleanup(void)
{
	unregister_test_probe(&test_before_probe);
	unregister_test_probe(&test_case_probe);
	unregister_test_probe(&test_after_probe);
	unregister_test_probe(&test_after2_probe);
}